#include "ray.h"

namespace RayTracing
{

    Ray Ray::reflect(const Point& point, const Point& normal) const
    {
        Point direction = m_direction - normal * 2 * (m_direction * normal);
        bg::detail::vec_normalize<Point>(direction);
        return Ray(point, direction);
    }

}