#pragma once
#include "rail/chassis/iholonomic_input.hpp"
#include "util/math/linear/vector_alias.hpp"

namespace fang::chassis
{
    using IHolonomicInput = rail::chassis::IHolonomicInput<math::AbstractVector2D, double>;
}