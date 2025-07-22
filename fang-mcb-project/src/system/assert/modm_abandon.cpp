#include "modm_abandon.hpp"
#include "driver/drivers_singleton.hpp"
void modm_abandon(const modm::AssertionInfo &info)
{
    //This forces the debugger to see it via copy constructor
    static modm::AssertionInfo readInfo = info; 
    //TODO: write to terminal or buzz in morse code

    //Create signal and preserve info
    DriversSingleton::getDrivers().pwm.write(1.0, tap::gpio::Pwm::Buzzer);
    while(true)
    {
        //Stop executoin completely
    }
}