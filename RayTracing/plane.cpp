#include "plane.h"

namespace  RayTracing
{

    void Plane::load(const YAML::Node& node)
    {
        Node::load(node);
        YAML::Node plane = node["plane"];
        m_position =
        {
            plane["position"]["x"].as<double>(),
            plane["position"]["y"].as<double>(),
            plane["position"]["z"].as<double>()
        };
        m_normal =
        {
            plane["normal"]["x"].as<double>(),
            plane["normal"]["y"].as<double>(),
            plane["normal"]["z"].as<double>()
        };
    }

    std::vector<Point> Plane::rayIntersetion(const Ray & ray) const
    {
        std::vector<Point> intersections;
        Ray tfRay = ray.transform(inverse(m_world));

        float nDotD = m_normal * tfRay.direction();
        if (nDotD < 0.0)
        {
            double t = (m_position* m_normal - tfRay.start() * m_normal) / nDotD;
            intersections.push_back(tfRay.eval(t).transform(m_world, 1.0));
        }

        return intersections;
    }

    Point Plane::normal(const Point & point) const
    {
        return m_normal;
    }

}