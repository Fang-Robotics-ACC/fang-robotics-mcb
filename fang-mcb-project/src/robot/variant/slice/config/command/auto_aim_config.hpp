#pragma once
#include "control/turret/gimbal/command/ballistics_aim_command.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::robot
{
    using namespace units::literals;
    static const turret::BallisticsAimCommand::Config kAutoAimConfig 
    {
        .bulletVelocity = 24_mps
    };
}