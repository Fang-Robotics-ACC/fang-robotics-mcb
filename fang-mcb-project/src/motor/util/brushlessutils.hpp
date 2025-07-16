#ifndef FANG_ROBOTICS_MCB_MOTOR_UTIL_BRUSHLESS_UTILS_HPP
#define FANG_ROBOTICS_MCB_MOTOR_UTIL_BRUSHLESS_UTILS_HPP
#include "unitaliases.hpp"

namespace motor::brushless
{
    /*!
    This provides the speed that the motor will output to achieve the
    given output voltage from the controller.*/
    RPM controllerVoltageToSpeed(const Volts& volts, const RPMPerVolt& kv);

    /*!
    This provides the voltage that the controller will output to achieve the
    given speed on the motor.*/
    Volts speedToControllerVoltage(const RPM& speed, const RPMPerVolt& kv);
}
#endif 