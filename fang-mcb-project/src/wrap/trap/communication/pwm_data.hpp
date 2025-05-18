#ifndef FANG_ROBOTICS_MCB_TRAP_PWM_DATA_HPP
#define FANG_ROBOTICS_MCB_TRAP_PWM_DATA_HPP
#include "unitaliases.hpp"

#include "tap/communication/gpio/pwm.hpp"

namespace trap
{
    namespace gpio
    {
        struct PwmData
        {
            tap::gpio::Pwm pwmPin;
            Hertz pinFrequency;
        };
    }//namespace gpio
}//namespace trap
#endif