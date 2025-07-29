#ifndef FANG_ROBOTICS_MCB_WRAP_RAIL_MOTOR_I_SPEED_MOTOR_HPP
#define FANG_ROBOTICS_MCB_WRAP_RAIL_MOTOR_I_SPEED_MOTOR_HPP

#include "rail/motor/ispeed_motor.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::motor
{
    using ISpeedMotor = rail::motor::ISpeedMotor<RPM>;
}
#endif