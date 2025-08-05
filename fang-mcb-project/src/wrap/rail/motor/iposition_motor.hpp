#pragma once

#include "rail/motor/iposition_motor.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::motor
{
    using IPositionMotor = rail::motor::IPositionMotor<Radians>;
}