#include "plane.h"

namespace  RayTracing
{

    Plane::Plane(const Point & position, const Point & rotation)
    {
        m_world = translate(position) * rotate(rotation);
    }

    void Plane::load()
    {
        m_world = translate({ 0.0, 0.0, -1.0 }) * rotate({0.0, M_PI/6, 0.0});
    }

    std::vector<Point> Plane::rayIntersetion(const Ray & ray) const
    {
        std::vector<Point> intersections;
        Ray tfRay = ray.transform(inverse(m_world));

        if (abs(tfRay.direction().z) > 1e-5)
        {
            double t = -tfRay.start().z / tfRay.direction().z;
            if(t > 0)
                intersections.push_back(tfRay.eval(t).transform(m_world, 1.0));
        }

        return intersections;
    }

    Point Plane::normal(const Point & point) const
    {
        return {0.0, 0.0, 1.0};
    }

}