#include "modm_abandon.hpp"
#include "driver/drivers_singleton.hpp"
#include "system/emergency/kill_system.hpp"
#include "system/error/signal/assert_failed_buzz.hpp"

void modm_abandon(const modm::AssertionInfo &info)
{
    //This forces the debugger to see it via copy constructor
    static modm::AssertionInfo readInfo = info; 
    //TODO: write to terminal or buzz in morse code
    Drivers& drivers{DriversSingleton::getDrivers()};
    fang::emergency::killSystem();

    fang::error::assertFailedBuzz(drivers.pwm);

    //Stop execution completely
    while(true)
    {
    }
}