#include "camera.h"

namespace RayTracing
{

    void Camera::load(YAML::Node & config)
    {
        YAML::Node camera = config["camera"];
        YAML::Node position = camera["position"];
        m_position = 
        { 
            position["x"].as<double>(),
            position["y"].as<double>(),
            position["z"].as<double>() 
        };

        YAML::Node orientation = camera["orientation"];
        Matrix r = rotate(
        { 
            orientation["p"].as<double>() * M_PI / 180.0,
            orientation["r"].as<double>() * M_PI / 180.0,
            orientation["h"].as<double>() * M_PI / 180.0
        });
        m_up = { 0.0, 0.0, 1.0 };
        m_up = m_up.transform(r, 0.0);
        m_right = { 1.0, 0.0, 0.0 };
        m_right = m_right.transform(r, 0.0);

        m_fovX = camera["fov_x"].as<double>();
        m_fovY = camera["fov_y"].as<double>();
        m_nclip = camera["near_clip"].as<double>();
    }

    Ray Camera::getCameraRay(double x, double y) const
    {
        Point forward = bg::cross_product<Point>(m_up, m_right);
        bg::detail::vec_normalize<Point>(forward);
        double screenX = tan(m_fovX * M_PI / 180.0);
        double screenY = tan(m_fovY * M_PI / 180.0);
        Point direction = forward + m_right * ((x - 0.5) * screenX) + m_up * ((0.5 - y) * screenY);
        bg::detail::vec_normalize(direction);
        return Ray(m_position, direction);
    }

    bool Camera::checkVisibility(const Point & point, const Point & newPoint) const
    {
        return bg::distance<Point, Point>(m_position, newPoint) < bg::distance<Point, Point>(m_position, point);
    }

}