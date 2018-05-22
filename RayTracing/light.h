#pragma once

#include <algorithm>
#include <yaml-cpp\yaml.h>

#include "point.h"
#include "ray.h"
#include "node.h"

namespace RayTracing
{

    class Light
    {

    public:
        Light() {}
        Light(const YAML::Node& light, const Point& camera);
        Ray getLightRay(const Point& point) const;
        Point getIllumination(const Point& point, const Point& normal, const Node& object, bool shaded) const;

    private:
        Point m_position, m_color, m_camera;
        double m_ambient, m_shine;
    };

}