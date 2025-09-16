#ifndef FANG_ROBOTICS_MCB_TURRET_AIM_CONFIG_HPP
#define FANG_ROBOTICS_MCB_TURRET_AIM_CONFIG_HPP
#include "control/turret/gimbal/command/positional_aim_command.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::robot
{
    using namespace units::literals;
    static const turret::PositionalAimCommand::Config kTurretAimConfig
    {
        .pitchScale = 1_deg,
        .yawScale = 1_deg,
        .pitchRange = {-25_deg, 10_deg}
    };
}
#endif