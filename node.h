#pragma once

#include <yaml-cpp\yaml.h>

#include "renderable.h"
#include "object3d.h"
#include "color.h"

namespace RayTracing
{

    class Node : public Renderable, public Object3D
    {

    public:
        virtual void load(const YAML::Node& node);
        Color*& color() { return m_color; }

    protected:
        Matrix m_world;
        Color* m_color;

    };

}