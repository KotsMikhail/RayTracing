#pragma once

#include "node.h"

namespace RayTracing
{

    class Plane : public Node
    {

    public:
        Plane() {};
        Plane(const Point& position, const Point& rotation);
        void load(/*YAML::Node& node*/);
        virtual std::vector<Point> rayIntersetion(const Ray& ray) const;
        virtual Point normal(const Point& point) const;

    private:
        Matrix m_world;

    };

}