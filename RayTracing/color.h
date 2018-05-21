#pragma once

#include <yaml-cpp\yaml.h>

#include "point.h"
#include "renderable.h"

namespace RayTracing
{

    enum class ColorType
    {
        MATERIAL,
        NORMAL,
        DISTANCE
    };

    class Color
    {

    public:
        virtual Point getColor(const Point& point) const = 0;

    };

    class NormalColor : public Color
    {

    public:
        NormalColor(const Renderable* object) : m_object(object) {}

        virtual Point getColor(const Point& point) const
        {
            Point color = m_object->normal(point);
            color = { abs(color.x), abs(color.y), abs(color.z) };
            return color * 255.0;
        }

    private:
        const Renderable* m_object;

    };

    class DistanceColor : public Color
    {

    public:
        DistanceColor(const Point& center, double maxDist) : m_center(center), m_maxDist(maxDist) {};

        virtual Point getColor(const Point& point) const
        {
            double dist = bg::distance<Point, Point>(m_center, point) / m_maxDist;
            if (dist > 1.0)
                dist = 1.0;
            Point color = { dist, dist, dist };
            return color * 255.0;
        }

    private:
        Point m_center;
        double m_maxDist;

    };

    class MaterialColor : public Color
    {

    public:
        MaterialColor() {}

        MaterialColor(const YAML::Node& node)
        {
            YAML::Node color = node["material"]["color"];
            m_color =
            {
                color["r"].as<double>(),
                color["g"].as<double>(),
                color["b"].as<double>()
            };
        }

        virtual Point getColor(const Point& point) const
        {
            return m_color * 255.0;
        }

    private:
        Point m_color;

    };

}