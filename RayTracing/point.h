#pragma once

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/qvm/vec.hpp>
#include <boost/qvm/vec_access.hpp>
#include <boost/qvm/vec_operations.hpp>
#include <boost/qvm/mat.hpp>
#include <boost/qvm/vec_mat_operations.hpp>
#include <boost/qvm/map_mat_mat.hpp>

namespace RayTracing
{

    namespace bq = boost::qvm;
    namespace bg = boost::geometry;

    typedef bq::vec<double, 4> Vector;
    typedef bq::mat<double, 4, 4> Matrix;

    struct Point
    {
        double x, y, z;

        Point operator+(const Point& other) const
        {
            return{ x + other.x, y + other.y, z + other.z };
        };

        Point operator-(const Point& other) const
        {
            return{ x - other.x, y - other.y, z - other.z };
        };

        Point operator-() const
        {
            return{ -x, -y, -z };
        };

        Point operator*(double value) const
        {
            return{ x * value, y * value, z * value };
        };

        Point operator/(double value) const
        {
            return{ x / value, y / value, z / value };
        };

        double operator*(const Point& value) const
        {
            return  x * value.x + y * value.y + z * value.z;
        };

        Point transform(const Matrix& transform, double w) const
        {
            Vector v;
            bq::A<0>(v) = x; bq::A<1>(v) = y; bq::A<2>(v) = z; bq::A<3>(v) = w;
            v = transform * v;
            if (w != 0)
                v = v / w;
            else
                bq::normalize(v);
            return{ bq::A<0>(v), bq::A<1>(v),bq::A<2>(v) };
        }

        void clamp(double min, double max)
        {
            x = std::min(std::max(x, 0.0), 1.0);
            y = std::min(std::max(y, 0.0), 1.0);
            z = std::min(std::max(z, 0.0), 1.0);
        }

    };

}

BOOST_GEOMETRY_REGISTER_POINT_3D(RayTracing::Point, double, cs::cartesian, x, y, z)

