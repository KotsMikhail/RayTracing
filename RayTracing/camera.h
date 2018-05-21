#pragma once

#include <iostream>
#include <cmath>
#include <boost\geometry\arithmetic\normalize.hpp>
#include <yaml-cpp\yaml.h>

#include "object3d.h"
#include "ray.h"

namespace RayTracing
{

    class Camera : public Object3D
    {

    public:
        void load(YAML::Node& config);
        Ray getCameraRay(double x, double y) const;
        bool checkVisibility(const Point& point, const Point& newPoint) const;
        Point position() const { return m_position; }
        
    private:
        Point m_position, m_up, m_right;
        double m_fovX, m_fovY, m_nclip;

    };

}