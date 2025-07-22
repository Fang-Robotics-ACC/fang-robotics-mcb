#ifndef FANG_ROBOTICS_MCB_TURRET_AIM_CONFIG_HPP
#define FANG_ROBOTICS_MCB_TURRET_AIM_CONFIG_HPP
#include "control/turret/command/aim_command.hpp"
#include "wrap/units/units_alias.hpp"

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