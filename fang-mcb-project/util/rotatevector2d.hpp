#ifndef FANG_ROBOTICS_MCB_UTIL_ROTATE_VECTOR_2D
#define FANG_ROBOTICS_MCB_UTIL_ROTATE_VECTOR_2D
#include "unitaliases.hpp"
#include "mathaliases.hpp"
#include "modm/math/geometry/vector2.hpp"

namespace util
{
    namespace math
    {
        mathAliases::AbstractVector2D rotateVector(const mathAliases::AbstractVector2D& vector, const Radians& rotationAngle);
    }
}
#endif