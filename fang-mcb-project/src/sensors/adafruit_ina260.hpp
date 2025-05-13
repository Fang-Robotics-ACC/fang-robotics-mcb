#ifndef FANG_ROBOTICS_MCB_ADAFRUIT_INA260_HPP
#define FANG_ROBOTICS_MCB_ADAFRUIT_INA260_HPP
#include "unitaliases.hpp"

namespace sensors
{
    /**
     * Todo:
     * 1. Before accepting pull request, double check that milliwatts and millivolts and milliamps
     * Refer to the arduino drivers when adapting this for modm. I would recommend copying the whole header and c++,
     * and then replacing functions with their modm/taproot analogs
     * 
     * 2. Before accepting the pull request, double check to make sure all dynamically allocated memory is deleted
     * 
     * Ada fruit drivers
     * https://github.com/adafruit/Adafruit_INA260/tree/master
     * 
     * This repo has the rest of the adafruit classes(for example, Adafruit_I2CDevice.h):
     * https://github.com/adafruit/Adafruit_BusIO
     * 
     * Arduino wire guide:
     * https://docs.arduino.cc/language-reference/en/functions/communication/wire/
     * 
     * IMPORTANT: NOTE THAT THEY DO NOT HAVE DESTRUCTORS OF THE DYNAMICALLY ALLOCATED MEMORY
     * MAKE SURE THAT THE MEMORY IS DEALLOCATED WITHIN THE DESTRUCTOR OR END OF THE FUNCTION
     * 
     * Apparently the practice of not having a destructor for classes in arduino code is more widepsread
     * than I would like to admit. Consider using smart pointers or statically allocated memory.
     */
    class AdafruitIna260
    {
    public:
        //Implement these functions. Feel free to add more private/public functions
        //No public variables however (plz)
        Milliamperes readCurrent() const;
        Millivolts readBusVoltage() const;
        Milliwatts readPower() const;

    };
}//namespace sensors
#endif