#pragma once
#include "rail/chassis/ichassis_input_handler.hpp"
#include "util/math/linear/vector_alias.hpp"

namespace fang::chassis
{
    using IChassisInputHandler = rail::chassis::IChassisInputHandler<math::AbstractVector2D, double>;
}