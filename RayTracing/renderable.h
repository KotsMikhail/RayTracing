#pragma once

#include <vector>

#include "point.h"
#include "ray.h"

namespace RayTracing
{

    class Renderable
    {

    public:
        virtual std::vector<Point> rayIntersetion(const Ray& ray) const = 0;
        virtual Point normal(const Point& point) const = 0;

    };

}