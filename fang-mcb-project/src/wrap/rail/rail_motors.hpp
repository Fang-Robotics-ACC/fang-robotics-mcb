#ifndef FANG_ROBOTICS_MCB_WRAP_RAIL_RAIL_MOTORS_HPP
#define FANG_ROBOTICS_MCB_WRAP_RAIL_RAIL_MOTORS_HPP
#include "wrap/units/units_alias.hpp"
#include "motor/ispeed_motor.hpp"

#include <rail/motor/iposition_motor.hpp>
#include <rail/motor/ispeed_wheel.hpp>

namespace fang::motor
{
    using IPositionMotor = rail::motor::IPositionMotor<Radians>;
    using ISpeedWheel = rail::motor::ISpeedWheel<MetersPerSecond>;
}
#endif