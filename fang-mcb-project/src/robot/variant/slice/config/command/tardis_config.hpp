#pragma once

#include "control/chassis/drive/holonomic/command/tardis_command.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::robot
{
    using namespace units::literals;
    static const chassis::AzrielShredder::Config k_razielKalmanShredderConfig
    {
        .biteDepth  = 0.9,
        .biteForce  = 5,
        .period     = 0.8, //every x seconds
        .phase      = 0,
    };

    static const chassis::TardisCommand::Config k_tardisConfig
    {
        .maxTranslation = {20_mph, 20_mph}, // HACK: Ultra Mk2 motors do not use feedback rpm loops
        .maxRotation = 350_rpm,
        .downscaleCoefficient       = 5,
        .razielKalmanShredderConfig = k_razielKalmanShredderConfig
    };
}