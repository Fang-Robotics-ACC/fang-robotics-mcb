#ifndef FANG_ROBOTICS_MCB_PIERCE_FIELD_MECANUM_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_FIELD_MECANUM_CONFIG_HPP
#include "control/chassis/drive/holonomic/command/counter_strike_command.hpp"

namespace fang::robot
{
    static const chassis::CounterStrikeCommand::Config kFieldMecanumConfig 
    {
        .maxTranslation = {12_mph, 12_mph},
        .maxRotation    = 300_rpm,
    };
}

#endif