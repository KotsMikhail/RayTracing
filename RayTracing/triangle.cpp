#include "triangle.h"

namespace RayTracing
{

    void Triangle::load(const YAML::Node & node)
    {
        Node::load(node);
        YAML::Node triangle = node["triangle"];
        m_a =
        {
            triangle["a"]["x"].as<double>(),
            triangle["a"]["y"].as<double>(),
            triangle["a"]["z"].as<double>()
        };
        m_b =
        {
            triangle["b"]["x"].as<double>(),
            triangle["b"]["y"].as<double>(),
            triangle["b"]["z"].as<double>()
        };
        m_c =
        {
            triangle["c"]["x"].as<double>(),
            triangle["c"]["y"].as<double>(),
            triangle["c"]["z"].as<double>()
        };
        m_a = m_a.transform(m_world, 1.0);
        m_b = m_b.transform(m_world, 1.0);
        m_c = m_c.transform(m_world, 1.0);
    }

    std::vector<Point> Triangle::rayIntersetion(const Ray & ray) const
    {
        std::vector<Point> intersections;

        Point normal = bg::cross_product(m_b - m_a, m_c - m_a);
        bg::detail::vec_normalize<Point>(normal);
        Plane plane(m_a, normal);
        std::vector<Point> tmp = plane.rayIntersetion(ray);
        if (tmp.size())
        {
            Point p = tmp[0];
            Point v = bg::cross_product(m_b - m_a, p - m_a);
            if (normal * v < 0)
                return intersections;
            v = bg::cross_product(m_c - m_b, p - m_b);
            if (normal * v < 0)
                return intersections;
            v = bg::cross_product(m_a - m_c, p - m_c);
            if (normal * v < 0)
                return intersections;
            intersections.push_back(p);
        }

        return intersections;
    }

    Point Triangle::normal(const Point & point) const
    {
        Point normal = bg::cross_product(m_b - m_a, m_c - m_a);
        bg::detail::vec_normalize<Point>(normal);
        return normal;
    }

}