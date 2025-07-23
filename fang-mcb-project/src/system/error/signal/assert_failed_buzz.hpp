#ifndef FANG_ROBOTICS_MCB_SYSTEM_ERROR_SIGNAL
#define FANG_ROBOTICS_MCB_SYSTEM_ERROR_SIGNAL
#include "tap/communication/sensors/buzzer/buzzer.hpp"
#include "tap/communication/gpio/pwm.hpp"
namespace fang::error
{
    void assertFailedBuzz(tap::gpio::Pwm& pwm);
}
#endif