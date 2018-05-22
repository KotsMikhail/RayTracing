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
        Color* const & color() const { return m_color; }
        Color*& color() { return m_color; }
        double kAmbient() const { return m_kAmbient; }
        double kDiffuse() const { return m_kDiffuse; }
        double kSpecular() const { return m_kSpecular; }
        double reflection() const { return m_reflection; }
        double refraction() const { return m_refraction; }

    protected:
        Matrix m_world;
        Color* m_color;
        double m_kAmbient, m_kDiffuse, m_kSpecular, m_reflection, m_refraction;

    };

}