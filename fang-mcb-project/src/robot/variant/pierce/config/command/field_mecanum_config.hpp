#ifndef FANG_ROBOTICS_MCB_PIERCE_FIELD_MECANUM_CONFIG_HPP
#define FANG_ROBOTICS_MCB_PIERCE_FIELD_MECANUM_CONFIG_HPP
#include "control/chassis/field_mecanum_command.hpp"
namespace control
{
    static const chassis::FieldMecanumCommand::Config k_fieldMecanumConfig 
    {
        10_mph, //max translation - for turret based strafe
        6.5_mph, //maxXtranslation
        6.5_mph, //maxYTranslatioon
        100_rpm, //maxRotation
        0.5_deg //maxAngularDisplacement
    };
}

#endif