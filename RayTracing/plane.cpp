#include "plane.h"

namespace  RayTracing
{

    void Plane::load(const YAML::Node& node)
    {
        Node::load(node);
        YAML::Node plane = node["plane"];
        if (plane["position"])
            m_position =
            {
                plane["position"]["x"].as<double>(),
                plane["position"]["y"].as<double>(),
                plane["position"]["z"].as<double>()
            };
        else
            m_position = { 0.0, 0.0, 0.0 };
        if (plane["normal"])
            m_normal =
            {
                plane["normal"]["x"].as<double>(),
                plane["normal"]["y"].as<double>(),
                plane["normal"]["z"].as<double>()
            };
        else
            m_normal = { 0.0, 0.0, 1.0 };
        m_position = m_position.transform(m_world, 1.0);
        m_normal = m_normal.transform(m_world, 0.0);
    }

    std::vector<Point> Plane::rayIntersetion(const Ray & ray) const
    {
        std::vector<Point> intersections;

        float nDotD = m_normal * ray.direction();
        if (nDotD < 0.0)
        {
            double t = (m_position* m_normal - ray.start() * m_normal) / nDotD;
            if(t > 0)
                intersections.push_back(ray.eval(t));
        }

        return intersections;
    }

    Point Plane::normal(const Point & point) const
    {
        return m_normal;
    }

}