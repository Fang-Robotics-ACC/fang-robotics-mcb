#ifndef FANG_ROBOTICS_MCB_PIERCE_CONFIG_COMMAND_TARDIS_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_CONFIG_COMMAND_TARDIS_CONFIG_HPP
#include "control/chassis/holonomic/command/tardis_command.hpp"

namespace fang 
{
    static const chassis::RazielKalmanShredder::Config k_razielKalmanShredderConfig
    {
        .biteDepth  = 0.3,
        .biteForce  = 10,
        .period     = 2, //every two seconds
        .phase      = 0,
    };

    static const chassis::TardisCommand::Config k_tardisConfig
    {
        .maxTranslation = {10_mph, 10_mph},
        .maxRotation = 125_rpm,
        .downscaleCoefficient       = 10,
        .razielKalmanShredderConfig = k_razielKalmanShredderConfig
    };
}
 
#endif