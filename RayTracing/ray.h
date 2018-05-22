#pragma once

#include "point.h"
#include "object3d.h"

namespace RayTracing
{

    class Ray
    {

    public:
        Ray(const Point& start, const Point& direction) :
            m_start(start), m_direction(direction) {};
        Point& start() { return m_start; };
        Point& direction() { return m_direction; };
        const Point& start() const { return m_start; };
        const Point& direction() const { return m_direction; };
        Point eval(double x) const { return m_start + m_direction * x; }
        Ray transform(const Matrix& world) const { return Ray(m_start.transform(world, 1.0), m_direction.transform(world, 0.0)); };
        Ray reflect(const Point& point, const Point& normal) const;

    private:
        Point m_start, m_direction;

    };

}