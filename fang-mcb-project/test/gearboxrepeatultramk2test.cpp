#include "driver/motor/repeat_robotics/repeat_ultra_mk2.hpp"
#include "wrap/units/units_alias.hpp"

#include "driver/drivers.hpp"
#include "tap/communication/gpio/pwm.hpp"

#include <gtest/gtest.h>

using namespace units::literals;
using namespace fang;

TEST(UltraMk2, zeroSpeed)
{
    {
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //For a unidirectional configuration, this is 0 rpm
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr double gearRatio{14.0};
    constexpr double stillDutyCycle{0.75};
    
    Drivers drivers{};
    motor::RepeatUltraMk2 motor{drivers, {controllerVoltage, {tap::gpio::Pwm::C1, frequency}, false, gearRatio}};

    EXPECT_CALL(drivers.pwm,write(stillDutyCycle, tap::gpio::Pwm::C1));

    motor.setTargetSpeed(0_rpm);
    }

    {
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //The default max speed is the maximum theoretical speed
    //For a bidirectional configuration, the minimum speed is the negative of the maximum theoretical speed
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr RPMPerVolt kv{1450};
    constexpr double gearRatio{14.0};
    constexpr double stillDutyCycle{0.75};

    
    Drivers drivers{};
    motor::RepeatUltraMk2 motor
    {
        drivers,
        {
            controllerVoltage,
            {tap::gpio::Pwm::C1, frequency}, 
            false, 
            gearRatio
        }
    };

    EXPECT_CALL(drivers.pwm,write(stillDutyCycle, tap::gpio::Pwm::C1));
    motor.setTargetSpeed(0_rpm);
    }    
}

TEST(UltraMk2, inversion)
{
    {
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //For a unidirectional configuration, this is 0 rpm
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr double gearRatio{14.0};
    static constexpr RPMPerVolt kKv{1450.0};
    RPM maxTheoreticalSpeed{(kKv * controllerVoltage) / gearRatio}; // A geared motor will be slower
    constexpr double expectedDutyCycle{0.5};


    
    Drivers drivers{};
    motor::RepeatUltraMk2 motor
    {
        drivers,
        {
            controllerVoltage,
            {tap::gpio::Pwm::C1, frequency}, 
            true, 
            gearRatio
        }
    };

    EXPECT_CALL(drivers.pwm, write(expectedDutyCycle, tap::gpio::Pwm::C1));

    //Since this is a bidirectional motor, its maximum speed will become its minimum (since the inversion multiplies it by -1)
    //This results in the speed controller driver sending the signal that corresponds to the minimum speed of the given rage
    motor.setTargetSpeed(maxTheoreticalSpeed);
    }

    {
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //The default max speed is the maximum theoretical speed
    //For a bidirectional configuration, the minimum speed is the negative of the maximum theoretical speed
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr double gearRatio{14.0};
    static constexpr RPMPerVolt kKv{1450.0};
    RPM maxTheoreticalSpeed{(kKv * controllerVoltage) / gearRatio}; // A geared motor will be slower
    constexpr double expectedDutyCycle{1.0};

    
    Drivers drivers{};
    motor::RepeatUltraMk2 motor
    {
        drivers,
        {
            controllerVoltage,
            {tap::gpio::Pwm::C1, frequency}, 
            true, 
            gearRatio
        }
    };

    EXPECT_CALL(drivers.pwm,write(expectedDutyCycle, tap::gpio::Pwm::C1));
    motor.setTargetSpeed(-maxTheoreticalSpeed);
    }    
}