#ifndef FANG_ROBOTICS_MCB_INFANTRY_HPP
#define FANG_ROBOTICS_MCB_INFANTRY_HPP
#include "drivers.hpp"

#include "control/pierce_config/pierce_chassis_config.hpp"
#include "control/pierce_config/pierce_turret_config.hpp"
#include "control/pierce_config/pierce_turret_motion_config.hpp"

#include "control/chassis/chassis_subsystem.hpp"
#include "control/turret/turret_subsystem.hpp"
#include "control/chassis/field_mecanum_command.hpp"
#include "control/turret/command/turret_aim_command.hpp"
namespace control
{
    /**
     * First Fang: Pierce
     * The first robot in Fang Robotics est. 2025
     */
    class Pierce
    {
    public:
        struct Config
        {
            chassis::ChassisSubsystem::ChassisConfig chassisConfig;
            turret::TurretSubsystem::Config turretConfig;
            config::motion::TurretConfig turretMotionConfig;
        };
        Pierce(Drivers& drivers);
        void initializeSubsystemCommands();
    private:
        void initializeSubsystems();
        void registerSubsystems();
        void setDefaultCommands();
        void registerIoMappings();

        const Config k_config
        {
            k_pierceChassisConfig,
            pierceConfig::k_turretConfig,
            pierceConfig::k_turretMotionConfig
        };

        Drivers& m_drivers;
        chassis::ChassisSubsystem m_chassis;
        turret::TurretSubsystem m_turret;

        chassis::FieldMecanumCommand m_fieldMecanumCommand;
        turret::TurretAimCommand m_turretAimCommand;
    };//class Robot
}//namspace control
#endif
