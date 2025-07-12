#ifndef FANG_ROBOTICS_MCB_GEARBOX_SPEED_HPP
#define FANG_ROBOTICS_MCB_GEARBOX_SPEED_HPP
#include "unitaliases.hpp"

namespace motor
{

    /**
     * The gear ratio is how many turns the motor makes per gearbox output shaft turn
     */
    inline RPM motorToShaftSpeed(const RPM& motorSpeed, double gearRatio);

    /**
     * The gear ratio is how many turns the motor makes per gearbox output shaft turn
     */
    inline RPM shaftToMotorSpeed(const RPM& shaftSpeed, double gearRatio);
}
#endif