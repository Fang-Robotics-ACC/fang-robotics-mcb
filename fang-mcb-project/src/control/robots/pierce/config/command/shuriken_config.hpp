#ifndef FANG_ROBOTICS_MCB_SHURIKEN_CONFIG_PIERCE_HPP
#define FANG_ROBOTICS_MCB_SHURIKEN_CONFIG_PIERCE_HPP
#include "control/chassis/shuriken_command.hpp"
namespace control
{
    static const chassis::ShurikenCommand::MotionConfig k_shurikenMotionConfig
    {
        10_mph, //max translation - for turret based strafe
        10_mph, //maxXtranslation
        10_mph, //maxYTranslatioon
        100_rpm, //maxRotation
        0.5_deg //maxAngularDisplacement
    };
    static const chassis::ShurikenCommand::Config k_shurikenConfig
    {
        125_rpm,
        k_shurikenMotionConfig
    };
}
#endif