#ifndef FANG_ROBOTICS_MCB_CHASSIS_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_CHASSIS_SUBSYSTEM_HPP
#include "drivers.hpp"
#include "tap/control/subsystem.hpp"
#include "motors/gearboxrepeatultramk2.hpp"

namespace control
{
    namespace chassis
    {
        
        class ChassisSubsystem : public tap::control::Subsystem
        {
        public:
        using DriveMotor = motors::GearboxRepeatUltraMk2;
        struct ChassisConfig
        {
            DriveMotor& frontLeft;
            DriveMotor& frontRight;
            DriveMotor& rearLeft;
            DriveMotor& rearRight;
        };

        ChassisSubsystem(Drivers& drivers, const ChassisConfig& chassisConfig);
        private:
            DriveMotor& m_frontLeftMotor;
            DriveMotor& m_frontRightMotor;
            DriveMotor& m_rearLeftMotor;
            DriveMotor& m_rearRightMotor;
        };
    }//namespace chassis
}//namespace control
#endif