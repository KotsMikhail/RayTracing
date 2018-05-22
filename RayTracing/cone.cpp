#include "cone.h"

namespace RayTracing
{

    void RayTracing::Cone::load(const YAML::Node & node)
    {
        Node::load(node);
        m_radius = node["cone"]["r"].as<double>();
        m_height = node["cone"]["h"].as<double>();
    }

    std::vector<Point> RayTracing::Cone::rayIntersetion(const Ray & ray) const
    {
        std::vector<Point> intersections;
        Ray tfRay = ray.transform(inverse(m_world));

        double ratio = m_radius / m_height;
        double a = tfRay.direction().x * tfRay.direction().x + tfRay.direction().y * tfRay.direction().y - (ratio * tfRay.direction().z)*(ratio * tfRay.direction().z);
        double b = 2.0 * (tfRay.direction().x * tfRay.start().x + tfRay.direction().y * tfRay.start().y - ratio * ratio * tfRay.direction().z * tfRay.start().z);
        double c = tfRay.start().x * tfRay.start().x + tfRay.start().y * tfRay.start().y - ratio * ratio * tfRay.start().z * tfRay.start().z;
        double d = b * b - 4 * a * c;

        if (d >= 0)
        {
            double t1 = (-b + sqrt(d)) / (2.0 * a);
            double t2 = (-b - sqrt(d)) / (2.0 * a);
            if (t1 > 0)
            {
                Point p = tfRay.eval(t1);
                if (p.z <= 0 && p.z >= -m_height)
                    intersections.push_back(p.transform(m_world, 1.0));
            }
            if (t2 > 0)
            {
                Point p = tfRay.eval(t2);
                if (p.z <= 0 && p.z >= -m_height)
                    intersections.push_back(p.transform(m_world, 1.0));
            }
        }

        Plane p({ 0.0, 0.0, -m_height }, { 0.0, 0.0, -1.0 });
        std::vector<Point> tmp = p.rayIntersetion(tfRay);
        if (tmp.size() > 0 && tmp[0].x * tmp[0].x + tmp[0].y * tmp[0].y < m_radius * m_radius)
            intersections.push_back(tmp[0].transform(m_world, 1.0));

        return intersections;
    }

    Point RayTracing::Cone::normal(const Point & point) const
    {
        Point norm;
        Point p = point.transform(inverse(m_world), 1.0);
        if (p.z < -m_height + 1e-5)
                norm = { 0.0, 0.0, -1.0 };
        else
            norm = { 2.0 * p.x, 2.0 * p.y, -2.0 * p.z * (m_radius / m_height) * (m_radius / m_height) };
        bg::detail::vec_normalize(norm);
        norm = norm.transform(bq::inverse(m_world), 0.0);
        return norm;
    }

}