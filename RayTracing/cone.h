#pragma once

#include <yaml-cpp\yaml.h>

#include "node.h"
#include "plane.h"

namespace RayTracing
{

    class Cone : public Node
    {

    public:
        void load(const YAML::Node& node);
        virtual std::vector<Point> rayIntersetion(const Ray& ray) const;
        virtual Point normal(const Point& point) const;

    private:
        double m_height, m_radius;

    };

}
