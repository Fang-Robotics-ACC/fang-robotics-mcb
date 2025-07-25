#ifndef FANG_ROBOTICS_MCB_PIERCE_CONFIG_COMMAND_TARDIS_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_CONFIG_COMMAND_TARDIS_CONFIG_HPP
#include "control/chassis/holonomic/command/tardis_command.hpp"

namespace fang 
{
    static const chassis::TardisCommand::MotionConfig k_tardisMotionConfig
    {
        10_mph, //max translation - for turret based strafe
        10_mph, //maxXtranslation
        10_mph, //maxYTranslatioon
        100_rpm, //maxRotation
        0.5_deg //maxAngularDisplacement
    };

    static const chassis::RazielKalmanShredder::Config k_razielKalmanShredderConfig
    {
        .biteDepth  = 0.3,
        .biteForce  = 10,
        .period     = 2, //every two seconds
        .phase      = 0,
    };

    static const chassis::TardisCommand::Config k_tardisConfig
    {
        .shurikenSpeed              = 125_rpm,
        .motionConfig               = k_tardisMotionConfig,
        .downscaleCoefficient       = 10,
        .razielKalmanShredderConfig = k_razielKalmanShredderConfig

    };
}
 
#endif