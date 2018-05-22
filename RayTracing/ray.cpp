#include "ray.h"

namespace RayTracing
{

    double RayTracing::Ray::fresnelCoeff(const Point & normal, double refractionCoeff) const
    {
        double cosi = std::min(std::max(m_direction * normal,-1.0), 1.0);
        double ei = 1.0;
        double et = refractionCoeff;

        if (cosi > 0)
            std::swap(ei, et);
        double sint = ei / et * sqrt(std::max(1 - cosi * cosi, 0.0));
        if (sint >= 1.0)
            return 1.0;

        double cost = sqrt(std::max(1 - sint * sint, 0.0));
        cosi = abs(cosi);
        double rOrth = (et * cosi - ei * cost) / (et * cosi + ei * cost);
        double rPar = (ei * cosi - et * cost) / (ei * cosi + et * cost);
        return (rOrth * rOrth + rPar * rPar) / 2.0;
    }

    Ray Ray::reflect(const Point& point, const Point& normal) const
    {
        Point start = point;
        if (m_direction * normal > 0.0)
            start = start + normal * BIAS;
        else
            start = start - normal * BIAS;

        Point direction = m_direction - normal * 2 * (m_direction * normal);
        bg::detail::vec_normalize<Point>(direction);
        return Ray(point, direction);
    }

    Ray* RayTracing::Ray::refract(const Point & point, const Point & normal, double refractionCoeff) const
    {
        double cosi = std::min(std::max(m_direction * normal, -1.0), 1.0);
        double ei = 1.0;
        double et = refractionCoeff;
        Point surfaceNormal = normal;

        if (cosi < 0.0)
            cosi = -cosi;
        else
        {
            std::swap(ei, et);
            surfaceNormal = -surfaceNormal;
        }
        double e = ei / et;
        double k = 1 - e * e * (1 - cosi * cosi);
        if (k < 0.0)
            return nullptr;
        
        Point start = point;
        if (m_direction * normal > 0.0)
            start = start + normal * BIAS;
        else
            start = start - normal * BIAS;

        return new Ray(start, m_direction * e + surfaceNormal * (e * cosi - sqrt(k)));
    }

}