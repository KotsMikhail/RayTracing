#include "sphere.h"

namespace RayTracing
{

    void RayTracing::Sphere::load(const YAML::Node & node)
    {
        Node::load(node);
        m_radius = node["sphere"]["r"].as<double>();
    }

    std::vector<Point> Sphere::rayIntersetion(const Ray& ray) const
    {
        std::vector<Point> intersections;
        Ray tfRay = ray.transform(inverse(m_world));

        double a = 1.0;
        double b = 2 * (tfRay.direction() * tfRay.start());
        double c = tfRay.start() * tfRay.start() - m_radius * m_radius;
        double d = b * b - 4 * a * c;

        if (d >= 0)
        {
            double x1 = (-b + sqrt(d)) / (2.0 * a);
            double x2 = (-b - sqrt(d)) / (2.0 * a);
            Point p1 = tfRay.eval(x1);
            Point p2 = tfRay.eval(x2);
            p1 = p1.transform(m_world, 1.0);
            p2 = p2.transform(m_world, 1.0);
            intersections.push_back(p1);
            intersections.push_back(p2);
        }

        return intersections;
    }

    Point Sphere::normal(const Point & point) const
    {
        Point norm = point.transform(bq::inverse(m_world), 1.0);
        bg::detail::vec_normalize<Point>(norm);
        norm = norm.transform(bq::inverse(m_world), 0.0);
        return norm;
    }
}