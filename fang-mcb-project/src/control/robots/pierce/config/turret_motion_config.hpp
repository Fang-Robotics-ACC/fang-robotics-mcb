#ifndef FANG_ROBOTICS_MCB_TURRET_MOTION_CONFIG_HPP
#define FANG_ROBOTICS_MCB_TURRET_MOTION_CONFIG_HPP
#include "control/turret/command/aim_command.hpp"
#include "unitaliases.hpp"
namespace control
{
    using namespace units::literals;
    static const turret::AimCommand::Config k_turretAimConfig
    {
        40_rpm,
        120_rpm
    };
}
#endif