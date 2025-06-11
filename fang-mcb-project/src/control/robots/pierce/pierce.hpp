#ifndef FANG_ROBOTICS_MCB_INFANTRY_HPP
#define FANG_ROBOTICS_MCB_INFANTRY_HPP
#include "drivers.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "control/chassis/field_mecanum_command.hpp"
#include "configuration/chassis_config.hpp"
#include "control/turret/turret_subsystem.hpp"

#include "control/robots/pierce/config/turret_config.hpp"
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
        turret::TurretSubsystem::Config turretConfig;
    };
        Pierce(Drivers& drivers);
        void initialize();
    private:
        void initializeSubsystems();
        void registerSubsystems();
        void setDefaultCommands();
        void registerIoMappings();

        static constexpr Config mk_config
        {
            k_turretConfig
        };

        Drivers& m_drivers;
        turret::TurretSubsystem m_turret;
        //chassis::ChassisSubsystem m_chassis;
        //chassis::FieldMecanumCommand m_fieldMecanumCommand;
    };//class Robot
}//namspace control
#endif
