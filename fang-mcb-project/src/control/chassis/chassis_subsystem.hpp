#ifndef FANG_ROBOTICS_MCB_CHASSIS_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_CHASSIS_SUBSYSTEM_HPP
#include "tap/control/subsystem.hpp"
#include "motors/gearboxrepeatultramk2.hpp"

namespace control
{
    namespace chassis
    {
        using DriveMotor = motors::GearboxRepeatUltraMk2;
        struct ChassisConfig
        {
            DriveMotor& frontLeft;
            DriveMotor& frontRight;
            DriveMotor& rearLeft;
            DriveMotor& rearRight;
        };
        class ChassisSubsystem : public tap::control::Subsystem
        {
        public:

        };
    }//namespace chassis
}//namespace control
#endif