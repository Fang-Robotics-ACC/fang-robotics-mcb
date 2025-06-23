#ifndef FANG_ROBOTICS_MCB_TRAP_DJI_MOTOR_ALIASES_HPP
#define FANG_ROBOTICS_MCB_TRAP_DJI_MOTOR_ALIASES_HPP
#include "wrap/trap/algorithms/smooth_pid.hpp"
#include "unitaliases.hpp"
#include <cstdint>
namespace trap
{
    namespace motor
    {
        using DjiMotorOutput = int16_t;
        using DjiSpeedPid = trap::algorithms::SmoothPid<RPM, DjiMotorOutput, Seconds>;
        using DjiPositionPid = trap::algorithms::SmoothPid<Radians, DjiMotorOutput, Seconds>;
    }//namespace motor
}//namespace trap
#endif