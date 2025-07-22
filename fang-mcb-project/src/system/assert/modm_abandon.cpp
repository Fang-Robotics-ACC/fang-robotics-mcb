#include "modm_abandon.hpp"
#include "driver/drivers_singleton.hpp"
#include "system/error/signal/assert_failed_buzz.hpp"

void modm_abandon(const modm::AssertionInfo &info)
{
    //This forces the debugger to see it via copy constructor
    static modm::AssertionInfo readInfo = info; 

    //TODO: write to terminal or buzz in morse code

    Drivers& drivers{DriversSingleton::getDrivers()};
    fang::error::assertFailedBuzz(drivers.pwm);

    //Prevent motors from flailing
    drivers.pwm.writeAllZeros();

    //Stop execution completely
    while(true)
    {
    }
}