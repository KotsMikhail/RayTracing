#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

#include "point.h"

namespace RayTracing
{

    class Bitmap
    {

    public:
        Bitmap(int height, int width) : m_image(height, width, CV_8UC3) {};

        void set(int x, int y, const Point& color)
        {
            m_image.at<cv::Vec3b>(y, x) = cv::Vec3b(color.z, color.y, color.x);
        }

        void save(const std::string& path)
        {
            cv::imwrite(path, m_image);
        }

    private:
        cv::Mat m_image;

    };

}