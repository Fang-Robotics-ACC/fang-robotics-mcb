#ifndef FANG_ROBOTICS_MCB_PIERCE_FIELD_MECANUM_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_FIELD_MECANUM_CONFIG_HPP
#include "control/chassis/drive/holonomic/command/counter_strike_command.hpp"

namespace fang::robot
{
    static const chassis::CounterStrikeCommand::Config k_fieldMecanumConfig 
    {
        .maxTranslation = {6.5_mph, 6.5_mph},
        .maxRotation    = 100_rpm,
    };
}

#endif