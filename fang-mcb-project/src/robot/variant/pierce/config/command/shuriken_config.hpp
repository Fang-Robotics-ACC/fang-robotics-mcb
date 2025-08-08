#ifndef FANG_ROBOTICS_MCB_SHURIKEN_CONFIG_PIERCE_HPP
#define FANG_ROBOTICS_MCB_SHURIKEN_CONFIG_PIERCE_HPP
#include "control/chassis/drive/holonomic/command/shuriken_command.hpp"
namespace fang::robot
{
    static const chassis::ShurikenCommand::Config kShurikenConfig
    {
        .maxTranslation = {25_mph, 25_mph},
        .shurikenSpeed          = 350_rpm,
        .downscaleCoefficient   = 5
    };
}
#endif