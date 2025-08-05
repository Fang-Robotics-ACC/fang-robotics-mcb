#ifndef FANG_ROBOTICS_MCB_GEARBOX_SPEED_HPP
#define FANG_ROBOTICS_MCB_GEARBOX_SPEED_HPP
#include "wrap/units/units_alias.hpp"

namespace fang::motor
{

    /**
     * The gear ratio is how many turns the motor makes per gearbox output shaft turn
     */
    RPM motorToShaftSpeed(const RPM& motorSpeed, double gearRatio);

    /**
     * The gear ratio is how many turns the motor makes per gearbox output shaft turn
     */
    RPM shaftToMotorSpeed(const RPM& shaftSpeed, double gearRatio);
}
#endif