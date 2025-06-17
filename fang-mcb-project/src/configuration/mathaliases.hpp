#ifndef FANG_ROBOTICS_MCB_MATH_ALIASES_HPP
#define FANG_ROBOTICS_MCB_MATH_ALIASES_HPP
#include "modm/math/geometry/vector.hpp"
#include "tap/algorithms/cmsis_mat.hpp"
#include "data/vector2d.hpp"

namespace math
{
    using AbstractVector2D = data::math::Vector2D<double>;

    template <uint16_t ROWS, uint16_t COLS>
    using Matrix = tap::algorithms::CMSISMat<ROWS, COLS>;
}
#endif