#include "motor/gearboxrepeatultramk2.hpp"
#include "wrap/units/units_alias.hpp"

#include "tap/drivers.hpp"
#include "tap/communication/gpio/pwm.hpp"

#include <gtest/gtest.h>

using namespace units::literals;
TEST(minSpeedTest, repeatUltraMk2)
{
    {
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //For a unidirectional configuration, this is 0 rpm
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr double gearRatio{14.0};

    
    tap::Drivers drivers{};
    motor::GearboxRepeatUltraMk2 motor{drivers, controllerVoltage, tap::gpio::Pwm::C1, frequency, motor::Directionality::UNIDIRECTIONAL, false, gearRatio};

    EXPECT_CALL(drivers.pwm,write(0.5, tap::gpio::Pwm::C1));

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

    
    tap::Drivers drivers{};
    motor::GearboxRepeatUltraMk2 motor{drivers, controllerVoltage, tap::gpio::Pwm::C1, frequency, motor::Directionality::BIDIRECTIONAL, false, gearRatio};

    EXPECT_CALL(drivers.pwm,write(0.5, tap::gpio::Pwm::C1));
    motor.setTargetSpeed(motor.getMinSpeed());
    }
}

TEST(minClampSpeedtest, repeatUltraMk2)
{
    {
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //For a unidirectional configuration, this is 0 rpm
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr double gearRatio{14.0};

    
    tap::Drivers drivers{};
    motor::GearboxRepeatUltraMk2 motor{drivers, controllerVoltage, tap::gpio::Pwm::C1, frequency, motor::Directionality::UNIDIRECTIONAL, false, gearRatio};

    EXPECT_CALL(drivers.pwm,write(0.5, tap::gpio::Pwm::C1));

    //Attempt to set it below the minimum speed
    motor.setTargetSpeed(-10_rpm);
    }

    {
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //The default max speed is the maximum theoretical speed
    //For a bidirectional configuration, the minimum speed is the negative of the maximum theoretical speed
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr RPMPerVolt kv{1450};
    constexpr double gearRatio{14.0};

    
    tap::Drivers drivers{};
    motor::GearboxRepeatUltraMk2 motor{drivers, controllerVoltage, tap::gpio::Pwm::C1, frequency, motor::Directionality::BIDIRECTIONAL, false, gearRatio};

    EXPECT_CALL(drivers.pwm,write(0.5, tap::gpio::Pwm::C1));
    //Attempt to set it below the minimum speed
    motor.setTargetSpeed(motor.getMinSpeed() - 100_rpm);
    }
}

TEST(maxSpeedTest, repeatUltraMk2)
{
    {
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //For a unidirectional configuration, this is 0 rpm
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr double gearRatio{14.0};
    constexpr double maxDutyCycle{1};

    
    tap::Drivers drivers{};
    motor::GearboxRepeatUltraMk2 motor{drivers, controllerVoltage, tap::gpio::Pwm::C1, frequency, motor::Directionality::UNIDIRECTIONAL, false, gearRatio};

    EXPECT_CALL(drivers.pwm,write(maxDutyCycle, tap::gpio::Pwm::C1));

    motor.setTargetSpeed(motor.getMaxSpeed());
    }

    {
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //The default max speed is the maximum theoretical speed
    //For a bidirectional configuration, the minimum speed is the negative of the maximum theoretical speed
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr RPMPerVolt kv{1450};
    constexpr double gearRatio{14.0};
    constexpr double maxDutyCycle{1};

    
    tap::Drivers drivers{};
    motor::GearboxRepeatUltraMk2 motor{drivers, controllerVoltage, tap::gpio::Pwm::C1, frequency, motor::Directionality::BIDIRECTIONAL, false, gearRatio};

    EXPECT_CALL(drivers.pwm,write(maxDutyCycle, tap::gpio::Pwm::C1));
    motor.setTargetSpeed(motor.getMaxSpeed());
    }    
}

TEST(maxClampSpeedTest, repeatUltraMk2)
{
    {
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //For a unidirectional configuration, this is 0 rpm
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr double gearRatio{14.0};
    constexpr double maxDutyCycle{1};

    
    tap::Drivers drivers{};
    motor::GearboxRepeatUltraMk2 motor{drivers, controllerVoltage, tap::gpio::Pwm::C1, frequency, motor::Directionality::UNIDIRECTIONAL, false, gearRatio};

    EXPECT_CALL(drivers.pwm,write(maxDutyCycle, tap::gpio::Pwm::C1));

    motor.setTargetSpeed(motor.getMaxSpeed() + 123.3_rpm);
    }

    {
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //The default max speed is the maximum theoretical speed
    //For a bidirectional configuration, the minimum speed is the negative of the maximum theoretical speed
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr RPMPerVolt kv{1450};
    constexpr double gearRatio{14.0};
    constexpr double maxDutyCycle{1};

    
    tap::Drivers drivers{};
    motor::GearboxRepeatUltraMk2 motor{drivers, controllerVoltage, tap::gpio::Pwm::C1, frequency, motor::Directionality::BIDIRECTIONAL, false, gearRatio};

    EXPECT_CALL(drivers.pwm,write(maxDutyCycle, tap::gpio::Pwm::C1));
    motor.setTargetSpeed(motor.getMaxSpeed() + 234.5_rpm);
    }    
}

TEST(zeroSpeedTest, repeatUltraMk2)
{
    {
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //For a unidirectional configuration, this is 0 rpm
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr double gearRatio{14.0};
    constexpr double stillDutyCycle{0.5};

    
    tap::Drivers drivers{};
    motor::GearboxRepeatUltraMk2 motor{drivers, controllerVoltage, tap::gpio::Pwm::C1, frequency, motor::Directionality::UNIDIRECTIONAL, false, gearRatio};

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

    
    tap::Drivers drivers{};
    motor::GearboxRepeatUltraMk2 motor{drivers, controllerVoltage, tap::gpio::Pwm::C1, frequency, motor::Directionality::BIDIRECTIONAL, false, gearRatio};

    EXPECT_CALL(drivers.pwm,write(stillDutyCycle, tap::gpio::Pwm::C1));
    motor.setTargetSpeed(0_rpm);
    }    
}

TEST(invertedTest, repeatUltraMk2)
{
    {
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //For a unidirectional configuration, this is 0 rpm
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr double gearRatio{14.0};
    constexpr double minimumDutyCycle{0.5};

    
    tap::Drivers drivers{};
    motor::GearboxRepeatUltraMk2 motor{drivers, controllerVoltage, tap::gpio::Pwm::C1, frequency, motor::Directionality::BIDIRECTIONAL, true, gearRatio};

    EXPECT_CALL(drivers.pwm, write(minimumDutyCycle, tap::gpio::Pwm::C1));

    //Since this is a bidirectional motor, its maximum speed will become its minimum (since the inversion multiplies it by -1)
    //This results in the speed controller driver sending the signal that corresponds to the minimum speed of the given rage
    motor.setTargetSpeed(motor.getMaxSpeed());
    }

    {
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //The default max speed is the maximum theoretical speed
    //For a bidirectional configuration, the minimum speed is the negative of the maximum theoretical speed
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr RPMPerVolt kv{1450};
    constexpr double gearRatio{14.0};
    constexpr double maxDutyCycle{1.0};

    
    tap::Drivers drivers{};

    motor::GearboxRepeatUltraMk2 motor{drivers, controllerVoltage, tap::gpio::Pwm::C1, frequency, motor::Directionality::BIDIRECTIONAL, true, gearRatio};

    EXPECT_CALL(drivers.pwm,write(maxDutyCycle, tap::gpio::Pwm::C1));
    motor.setTargetSpeed(motor.getMinSpeed());
    }    

    {
    //Inversion should be ignored for unidirectional motor
    //The speed at the minimum range coresponds to a 1ms pulse to the vortex controller
    //The default max speed is the maximum theoretical speed
    //For a bidirectional configuration, the minimum speed is the negative of the maximum theoretical speed
    constexpr Volts controllerVoltage{24};
    constexpr Hertz frequency{500};
    constexpr RPMPerVolt kv{1450};
    constexpr double gearRatio{14.0};
    constexpr double maxDutyCycle{1.0};

    
    tap::Drivers drivers{};

    motor::GearboxRepeatUltraMk2 motor{drivers, controllerVoltage, tap::gpio::Pwm::C1, frequency, motor::Directionality::UNIDIRECTIONAL, true, gearRatio};

    EXPECT_CALL(drivers.pwm,write(maxDutyCycle, tap::gpio::Pwm::C1));
    motor.setTargetSpeed(motor.getMaxSpeed());
    }    
}