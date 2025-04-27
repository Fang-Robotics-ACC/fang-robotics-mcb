#ifndef BRUSHLESS_UTILS_HPP_SEFSDFSEF
#define BRUSHLESS_UTILS_HPP_SEFSDFSEF
#include "unitaliases.hpp"

namespace motors
{
    namespace util
    {
        const RPM& controllerVoltageToSpeed(const Volts& volts, const RPMPerVolt& kv);
        const Volts& speedToControllerVoltage(const RPM& speed, const RPMPerVolt& kv);
    }
}
#endif 