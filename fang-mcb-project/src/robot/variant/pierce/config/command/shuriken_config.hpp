#ifndef FANG_ROBOTICS_MCB_SHURIKEN_CONFIG_PIERCE_HPP
#define FANG_ROBOTICS_MCB_SHURIKEN_CONFIG_PIERCE_HPP
#include "control/chassis/drive/holonomic/command/shuriken_command.hpp"
namespace fang::robot
{
    static const chassis::ShurikenCommand::Config k_shurikenConfig
    {
        .maxTranslation = {6.5_mph, 6.5_mph},
        .shurikenSpeed          = 300_rpm,
        .downscaleCoefficient   = 10
    };
}
#endif