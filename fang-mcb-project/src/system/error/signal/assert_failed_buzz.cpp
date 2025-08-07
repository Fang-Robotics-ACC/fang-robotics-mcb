#include "assert_failed_buzz.hpp"
namespace fang::error
{
    void playFailedAssertBuzz(tap::gpio::Pwm& pwm)
    {
    //Create signal and preserve info
    constexpr int kAbandonFrequency{220};
    constexpr float kBuzzerVolume{0.005};

    pwm.write(kBuzzerVolume, tap::gpio::Pwm::Buzzer);
    tap::buzzer::playNote(&pwm, kAbandonFrequency);
    }
}