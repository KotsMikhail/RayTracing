#include "node.h"

namespace RayTracing
{

    void Node::load(const YAML::Node& node)
    {
        YAML::Node lcs = node["lcs"];
        Matrix t = translate(
        { 
            lcs["x"].as<double>(),
            lcs["y"].as<double>(),
            lcs["z"].as<double>()
        });
        Matrix r = rotate(
        {
            lcs["p"].as<double>() * M_PI / 180.0,
            lcs["r"].as<double>() * M_PI / 180.0,
            lcs["h"].as<double>() * M_PI / 180.0
        });
        Matrix s = scale(
        {
            lcs["sx"].as<double>(),
            lcs["sy"].as<double>(),
            lcs["sz"].as<double>()
        });
        m_world = t * r * s;
    }

}