#include "modm_abandon.hpp"
#include "driver/drivers_singleton.hpp"
void modm_abandon(const modm::AssertionInfo &info)
{
    constexpr float kAbandonFrequency{220};
    constexpr float kBuzzerVolume{0.005};
    constexpr auto kBuzzerTimer{tap::gpio::Pwm::TIMER4};
    //This forces the debugger to see it via copy constructor
    static modm::AssertionInfo readInfo = info; 
    //TODO: write to terminal or buzz in morse code

    Drivers& drivers{DriversSingleton::getDrivers()};
    //Create signal and preserve info
    drivers.pwm.setTimerFrequency(kBuzzerTimer, kAbandonFrequency);
    drivers.pwm.write(kBuzzerVolume, tap::gpio::Pwm::Buzzer);

    //Required for buzzing to occur
    while(true)
    {

        drivers.update();
        //Stop execution completely
    }
}