#pragma once

#include <yaml-cpp\yaml.h>

#include "node.h"
#include "point.h"
#include "plane.h"

namespace RayTracing
{

    class Triangle : public Node
    {

    public:
        virtual void load(const YAML::Node& node);
        virtual std::vector<Point> rayIntersetion(const Ray& ray) const;
        virtual Point normal(const Point& point) const;

    private:
        Point m_a, m_b, m_c;

    };

}