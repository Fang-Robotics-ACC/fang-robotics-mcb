#pragma once

#include "control/chassis/drive/holonomic/command/counter_strike_command.hpp"
#include "wrap/units/units_alias.hpp"
namespace fang::robot
{
    using namespace units::literals;
    static const chassis::CounterStrikeCommand::Config kFieldMecanumConfig 
    {
        .maxTranslation = {25_mph, 25_mph}, // HACK: Ultra Mk2 motors do not use feedback rpm loops
        .maxRotation    = 150_rpm,
    };
}

