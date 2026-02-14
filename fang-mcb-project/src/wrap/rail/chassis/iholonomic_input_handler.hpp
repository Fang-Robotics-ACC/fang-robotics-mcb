#pragma once
#include "rail/chassis/iholonomic_input_handler.hpp"
#include "util/math/linear/vector_alias.hpp"

namespace fang::chassis
{
    using IHolonomicInputHandler = rail::chassis::IHolonomicInputHandler<math::AbstractVector2D, double>;
}