#pragma once

#include <yaml-cpp\yaml.h>

#include "node.h"
#include "point.h"

namespace RayTracing
{

    class Plane : public Node
    {

    public:
        Plane() {};
        Plane(const Point& position, const Point& normal) : m_position(position), m_normal(normal) { m_world = scale({ 1.0, 1.0, 1.0 }); }
        virtual void load(const YAML::Node& node);
        virtual std::vector<Point> rayIntersetion(const Ray& ray) const;
        virtual Point normal(const Point& point) const;

    private:
        Point m_position, m_normal;

    };

}