#ifndef FANG_ROBOTICS_MCB_SHURIKEN_CONFIG_PIERCE_HPP
#define FANG_ROBOTICS_MCB_SHURIKEN_CONFIG_PIERCE_HPP
#include "control/chassis/holonomic/command/shuriken_command.hpp"
namespace fang 
{
    static const chassis::ShurikenCommand::MotionConfig k_shurikenMotionConfig
    {
        10_mph, //max translation - for turret based strafe
        14_mph, //maxXtranslation
        14_mph, //maxYTranslatioon
        100_rpm, //maxRotation
        0.5_deg //maxAngularDisplacement
    };
    static const chassis::ShurikenCommand::Config k_shurikenConfig
    {
        .shurikenSpeed          = 125_rpm,
        .motionConfig           = k_shurikenMotionConfig,
        .downscaleCoefficient   = 10
    };
}
#endif