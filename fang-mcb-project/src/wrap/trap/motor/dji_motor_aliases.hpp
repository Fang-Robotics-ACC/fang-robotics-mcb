#ifndef FANG_ROBOTICS_MCB_TRAP_DJI_MOTOR_ALIASES_HPP
#define FANG_ROBOTICS_MCB_TRAP_DJI_MOTOR_ALIASES_HPP
#include "rail/motor/ioutput_motor.hpp"
#include "wrap/trap/algorithms/smooth_pid.hpp"
#include "wrap/units/units_alias.hpp"

#include <cstdint>

namespace trap
{
    namespace motor
    {
        using DjiMotorOutput = int16_t;
        using DjiSpeedPid = trap::algorithms::SmoothPid<RPM, DjiMotorOutput, Seconds>;
        using DjiPositionPid = trap::algorithms::SmoothPid<Radians, DjiMotorOutput, Seconds>;
        using IDjiOutputMotor = rail::motor::IOutputMotor<DjiMotorOutput>;
    }//namespace motor
}//namespace trap
#endif