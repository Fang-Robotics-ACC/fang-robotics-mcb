#ifndef BRUSHLESS_UTILS_HPP_SEFSDFSEF
#define BRUSHLESS_UTILS_HPP_SEFSDFSEF
#include "unitaliases.hpp"

namespace motor
{
    namespace util 
    {
        namespace brushless 
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
    }
}
#endif 