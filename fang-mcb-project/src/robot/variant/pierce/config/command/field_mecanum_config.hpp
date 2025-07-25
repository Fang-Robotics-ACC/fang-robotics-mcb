#ifndef FANG_ROBOTICS_MCB_PIERCE_FIELD_MECANUM_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_FIELD_MECANUM_CONFIG_HPP
#include "control/chassis/holonomic/command/counter_strike_command.hpp"

namespace fang 
{
    static const chassis::CounterStrikeCommand::Config k_fieldMecanumConfig 
    {
        6.5_mph, //maxXtranslation
        6.5_mph, //maxYTranslatioon
        100_rpm, //maxRotation
    };
}

#endif