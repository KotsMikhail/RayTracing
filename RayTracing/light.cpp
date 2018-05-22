#include "light.h"

namespace RayTracing
{

    RayTracing::Light::Light(const YAML::Node& light, const Point& camera)
    {
        YAML::Node position = light["position"];
        m_position =
        {
            position["x"].as<double>(),
            position["y"].as<double>(),
            position["z"].as<double>()
        };
        YAML::Node color = light["color"];
        m_color =
        {
            color["r"].as<double>(),
            color["g"].as<double>(),
            color["b"].as<double>()
        };
        m_camera = camera;
        m_ambient = light["ambient"].as<double>();
        m_shine = light["shine"].as<double>();
    }

    Ray Light::getLightRay(const Point& point) const
    {
        Point direction = m_position - point;
        bg::detail::vec_normalize<Point>(direction);
        return Ray(point, direction);
    }

    Point Light::getIllumination(const Point& point, const Point& normal, const Node& object, bool shaded) const
    {
        if (shaded)
            return m_color * object.kAmbient() * m_ambient;

        Point l = m_position - point;
        bg::detail::vec_normalize<Point>(l);
        Point h = m_camera - point;
        bg::detail::vec_normalize<Point>(h);
        Point r = -l + normal * 2 * (l * normal);
        bg::detail::vec_normalize<Point>(r);

        double diff = object.kDiffuse() * (normal * l);
        double spec = object.kSpecular() * pow(std::max(r * h, 0.0), m_shine);

        return m_color * (object.kAmbient() * m_ambient + diff + spec);
    }

}