#pragma once

#include "rail/motor/ispeed_wheel.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::motor
{
    using ISpeedWheel = rail::motor::ISpeedWheel<MetersPerSecond>;
}
