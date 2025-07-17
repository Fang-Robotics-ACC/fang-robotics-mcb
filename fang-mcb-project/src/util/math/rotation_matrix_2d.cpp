#include "util/math/geometry/rotate_vector_2d.hpp"
#include <math.h>
namespace math
{
    Matrix<2, 2> rotationMatrix2D(const Radians& angle)
    {
        //https://en.wikipedia.org/wiki/Rotation_matrix
        const float theta{angle.to<float>()};
        return Matrix<2, 2>
        {{
            std::cos(theta), -std::cos(theta),
            std::sin(theta),  std::cos(theta)}};
    }
}