#ifndef FANG_ROBOTICS_MCB_PIERCE_FIELD_MECANUM_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_FIELD_MECANUM_CONFIG_HPP
#include "control/chassis/drive/holonomic/command/counter_strike_command.hpp"

namespace fang::robot
{
    static const chassis::CounterStrikeCommand::Config kFieldMecanumConfig 
    {
        .maxTranslation = {25_mph, 25_mph}, // HACK: Ultra Mk2 motors do not use feedback rpm loops
        .maxRotation    = 150_rpm,
    };
}

#endif