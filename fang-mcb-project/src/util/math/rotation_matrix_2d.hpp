#ifndef FANG_ROBOTICS_MCB_UTIL_MATH_2D_ROTATION_MATRIX
#define FANG_ROBOTICS_MCB_UTIL_MATH_2D_ROTATION_MATRIX
#include "mathaliases.hpp"
#include "unitaliases.hpp"
namespace math
{
    /**
     * Generates a 2d rotation matrix
     */
    Matrix<2, 2> rotationMatrix2D(const Radians& angle);
}
#endif