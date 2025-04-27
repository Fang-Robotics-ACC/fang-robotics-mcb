#include "brushlessfunctions.hpp"

namespace motors
{
    namespace util
    {
        const RPM& controllerVoltageToSpeed(const Volts& volts, const RPMPerVolt& kv)
        {
            return volts * kv; //The kv constant multiplied by the volts = the rpm
        }

        const Volts& speedToControllerVoltage(const RPM& speed, const RPMPerVolt& kv)
        {
            return speed / kv; //The kv constant multiplied by the volts = the rpm
        }
    }

}
