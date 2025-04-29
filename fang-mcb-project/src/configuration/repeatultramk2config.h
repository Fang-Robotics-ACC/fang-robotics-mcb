#ifndef REPEAT_ULTRA_MK_CONFIG_H_SFELFKJSDKLFJASDF
#define REPEAT_ULTRA_MK_CONFIG_H_SFELFKJSDKLFJASDF
#include "unitaliases.hpp"
namespace motors
{
    // The Vortex uses a range of pulses between 1 to 2 milliseconds via rc pwm
    const Milliseconds mk_vortexESCPeriod{2};
    // This should be 500 kHz
    const Hertz mk_vortexPWMFrequency{1.0/mk_vortexESCPeriod};
}
#endif