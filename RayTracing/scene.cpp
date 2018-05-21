#include "scene.h"

namespace RayTracing
{

    void Scene::load(const std::string& path, ColorType ctype, const boost::any& param)
    {
        YAML::Node config = YAML::LoadFile("D:\\SPBPU\\4_grade\\Graphics\\RayTracing\\RayTracing\\scene_axes.yml");
        m_camera.load(config);

        YAML::Node scene = config["scene"];
        for (auto i = scene.begin(); i != scene.end(); i++)
        {
            YAML::Node node = (*i)["node"];
            bool asdf = node["lcs"];
            Node* object = getObject(node, ctype, param);
            m_objects.push_back(object);
        }
    }

    Bitmap Scene::render(int resolutionX, int resolutionY) const
    {
        Bitmap result(resolutionX, resolutionY);
        for (int x = 0; x < resolutionX; x++)
            for (int y = 0; y < resolutionY; y++)
            {
                Ray ray = m_camera.getCameraRay((double)x / resolutionX, (double)y / resolutionY);
                result.set(x, y, getRayIntersection(ray));
            }
        return result;
    }

    Point RayTracing::Scene::getRayIntersection(const Ray& ray) const
    {
        Point color = BACKGROUND;
        Point point = { std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max() };
        for (auto obj = m_objects.begin(); obj != m_objects.end(); obj++)
        {
            std::vector<Point> intersections = (*obj)->rayIntersetion(ray);
            for(auto newPoint = intersections.begin(); newPoint != intersections.end(); newPoint++)
                if (m_camera.checkVisibility(point, *newPoint))
                {
                    point = *newPoint;
                    color = (*obj)->color()->getColor(point);
                }
        }
        return color;
    }

    Node* Scene::getObject(const YAML::Node& node, ColorType ctype, const boost::any& param) const
    {
        Node* object;

        if (node["sphere"])
            object = new Sphere();
        else if (node["cylinder"])
            object = new Cylinder();
        else
            throw std::runtime_error("Unknown object");

        object->load(node);
        
        Color* color = nullptr;
        double maxDist = 0.0;
        switch (ctype)
        {
        case ColorType::MATERIAL:
            color = new MaterialColor(node);
            break;
        case ColorType::NORMAL:
            color = new NormalColor(object);
            break;
        case ColorType::DISTANCE:
            maxDist = boost::any_cast<double>(param);
            color = new DistanceColor(m_camera.position(), maxDist);
            break;
        default:
            throw std::runtime_error("Unsupported color type");
            break;
        };
        object->color() = color;

        return object;
    }

}