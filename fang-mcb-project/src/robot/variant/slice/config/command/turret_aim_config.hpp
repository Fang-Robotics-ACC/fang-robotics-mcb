#pragma once

#include "control/turret/gimbal/command/aim_command.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::robot
{
    using namespace units::literals;
    static const turret::AimCommand::Config kTurretAimConfig
    {
        .maxPitchSpeed = 40_rpm,
        .maxYawSpeed = 120_rpm,
        .pitchRange = {-25_deg, 10_deg}
    };
}
