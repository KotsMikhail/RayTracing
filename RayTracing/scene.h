#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include <boost\any.hpp>
#include <yaml-cpp\yaml.h>

#include "camera.h"
#include "bitmap.h"
#include "plane.h"
#include "triangle.h"
#include "sphere.h"
#include "cylinder.h"
#include "color.h"
#include "light.h"

namespace RayTracing
{

#define BACKGROUND {0.0, 0.0, 0.0}

    class Scene
    {

    public:
        void load(const std::string& path, ColorType ctype, const boost::any& param);
        Bitmap render(int resolutionX, int resolutionY) const;

    private:
        Point getRayIntersection(const Ray& ray) const;
        Node* getObject(const YAML::Node& node, ColorType ctype, const boost::any& param = nullptr) const;

        std::vector<Node*> m_objects;
        std::vector<Light*> m_lights;
        Camera m_camera;

    };

}