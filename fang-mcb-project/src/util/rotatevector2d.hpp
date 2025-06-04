#ifndef FANG_ROBOTICS_MCB_UTIL_ROTATE_VECTOR_2D
#define FANG_ROBOTICS_MCB_UTIL_ROTATE_VECTOR_2D
#include "unitaliases.hpp"
#include "mathaliases.hpp"
#include "modm/math/geometry/vector2.hpp"

namespace util
{
    namespace math
    {
        /**
         * This algorithm has an accuracy of within 1e-14; however, rotating the vector back will produce accuracy to only within
         * 1e-10
         */
        ::math::AbstractVector2D rotateVector2D(const ::math::AbstractVector2D& vector, const Radians& rotationAngle);
    }
}
#endif