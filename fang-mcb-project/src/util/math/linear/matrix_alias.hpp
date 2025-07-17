#ifndef FANG_ROBOTICS_MCB_UTIL_MATH_LINEAR_MATRIX_ALIAS_HPP
#define FANG_ROBOTICS_MCB_UTIL_MATH_LINEAR_MATRIX_ALIAS_HPP
#include "modm/math/matrix.hpp"
namespace math
{
    template <uint16_t ROWS, uint16_t COLS>
    using Matrix = tap::algorithms::CMSISMat<ROWS, COLS>;
}
#endif