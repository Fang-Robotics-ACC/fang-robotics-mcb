#ifndef FANG_ROBOTICS_MCB_INFANTRY_HPP
#define FANG_ROBOTICS_MCB_INFANTRY_HPP
#include "drivers.hpp"
#include "configuration/motion/turret_motion_config.hpp"


#include "control/chassis/chassis_subsystem.hpp"
#include "control/chassis/field_mecanum_command.hpp"
#include "configuration/chassis_config.hpp"
#include "control/turret/turret_subsystem.hpp"

#include "control/robots/pierce/config/turret_config.hpp"
#include "control/robots/pierce/config/turret_motion_config.hpp"

//Commands
#include "control/turret/command/aim_command.hpp"
#include "control/turret/command/activate_booster_command.hpp"
#include "control/robots/pierce/command_mapping/activate_booster_command_map.hpp"

#include "trap/communication/sensors/imu.hpp"

#include "tap/control/hold_command_mapping.hpp"

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
        config::motion::TurretMotionConfig turretMotionConfig;
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
            k_turretMotionConfig,
            k_turretConfig
        };

        config::motion::TurretMotionConfig turretMotionConfig;

        Drivers& m_drivers;
        trap::communication::sensors::Imu m_imu;

        turret::TurretSubsystem m_turret;

        turret::AimCommand m_aimCommnd;
        turret::ActivateBoosterCommand m_activateBoosterCommand;

        tap::control::HoldCommandMapping m_activateBoosterCommandMapping{&m_drivers, {&m_activateBoosterCommand}, tap::control::RemoteMapState{tap::communication::serial::Remote::Switch::LEFT_SWITCH, tap::communication::serial::Remote::SwitchState::UP}};
        chassis::ChassisSubsystem m_chassis;
        chassis::FieldMecanumCommand m_fieldMecanumCommand;

    };//class Robot
}//namspace control
#endif
