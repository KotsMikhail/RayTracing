#pragma once

#include "point.h"

#ifndef M_PI
    #define M_PI 3.14159265358979 // For some reason, MSVC doesn't define this when <cmath> is included
#endif

namespace RayTracing
{

    typedef bg::strategy::transform::matrix_transformer<double, 3, 3> MatrixTransform;

    class Object3D
    {

    protected:
        Matrix translate(const Point& v) const
        {
            return MatrixTransform(
                1.0, 0.0, 0.0, v.x,
                0.0, 1.0, 0.0, v.y,
                0.0, 0.0, 1.0, v.z,
                0.0, 0.0, 0.0, 1.0
            ).matrix();
        };

        Matrix rotate(const Point& angle) const
        {
            MatrixTransform rotateX = MatrixTransform(
                1.0, 0.0, 0.0, 0.0,
                0.0, cos(angle.x), -sin(angle.x), 0.0,
                0.0, sin(angle.x), cos(angle.x), 0.0,
                0.0, 0.0, 0.0, 1.0
            );
            MatrixTransform rotateY = MatrixTransform(
                cos(angle.y), 0.0, sin(angle.y), 0.0,
                0.0, 1.0, 0.0, 0.0,
                -sin(angle.y), 0.0, cos(angle.y), 0.0,
                0.0, 0.0, 0.0, 1.0
            );
            MatrixTransform rotateZ = MatrixTransform(
                cos(angle.z), -sin(angle.z), 0.0, 0.0,
                sin(angle.z), cos(angle.z), 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0
            );
            return rotateZ.matrix() * rotateY.matrix() * rotateX.matrix();
        };

        Matrix scale(const Point& scale) const
        {
            return MatrixTransform(
                scale.x, 0.0, 0.0, 0.0,
                0.0, scale.y, 0.0, 0.0,
                0.0, 0.0, scale.z, 0.0,
                0.0, 0.0, 0.0, 1.0
            ).matrix();
        };

    };

}