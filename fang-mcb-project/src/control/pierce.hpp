#ifndef FANG_ROBOTICS_MCB_INFANTRY_HPP
#define FANG_ROBOTICS_MCB_INFANTRY_HPP
#include "drivers.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "control/chassis/field_mecanum_command.hpp"
namespace control
{
    /**
     * First Fang: Pierce
     * The first robot in Fang Robotics est. 2025
     */
    class Pierce
    {
    public:
        Pierce(Drivers& drivers);
        void initializeSubsystemCommands();
    private:
        void initializeSubsystems();
        void registerSubsystems();
        void setDefaultCommands();
        void registerIoMappings();

        Drivers& m_drivers;
        chassis::ChassisSubsystem m_chassis;
        chassis::FieldMecanumCommand m_fieldMecanumCommand;

    };//class Robot
}//namspace control
#endif
