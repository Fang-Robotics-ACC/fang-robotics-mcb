#include <gtest/gtest.h>

#include "motors/vortex80aesc.hpp"
#include "trap/communication/pwm_data.hpp"
#include "unitaliases.hpp"
#include "drivers.hpp"

#include "units.h"

#include "tap/communication/gpio/pwm.hpp"

using namespace units::literals;

Drivers drivers{};
trap::gpio::PwmData pwmData{tap::gpio::Pwm::C1, 500_Hz};
trap::gpio::PwmData nonStandardPwmData{tap::gpio::Pwm::C1, 250_Hz};


TEST(zeroTest, Vortex80AEsc)
{
    //2 ms period
    const Hertz standardFrequency{500};
    logic::motors::Vortex80AEsc vortex {drivers.pwm, pwmData};

    EXPECT_DOUBLE_EQ(vortex.adaptedDutyCycle(0.0, standardFrequency), 0.5);
}

TEST(midRangeTest, Vortex80AEsc)
{

    const Hertz standardFrequency{500};
    //2 ms period
    logic::motors::Vortex80AEsc vortex {drivers.pwm, pwmData};

    EXPECT_DOUBLE_EQ(vortex.adaptedDutyCycle(0.5, standardFrequency), 0.75);
}

TEST(fullRangeTest, Vortex80AEsc)
{
    const Hertz standardFrequency{500};
    //2 ms period
    logic::motors::Vortex80AEsc vortex {drivers.pwm, pwmData};

    EXPECT_DOUBLE_EQ(vortex.adaptedDutyCycle(1, standardFrequency), 1.0);
}

TEST(oddRangeTest, Vortex80AEsc)
{
    const Hertz nonStandardFrequency{250};
    //4 ms period
    logic::motors::Vortex80AEsc vortex {drivers.pwm, nonStandardPwmData};

    EXPECT_DOUBLE_EQ(vortex.adaptedDutyCycle(1, nonStandardFrequency), 0.5);
}

TEST(bidirectionalTest, Vortex80AEsc)
{
    logic::motors::Vortex80AEsc vortex {drivers.pwm, pwmData};

    EXPECT_DOUBLE_EQ(vortex.calculateDutyCycle(-1.0), 0.5);
    EXPECT_DOUBLE_EQ(vortex.calculateDutyCycle(0.0), 0.75);
    EXPECT_DOUBLE_EQ(vortex.calculateDutyCycle(1.0), 1.0);
}

TEST(unidirectionalTest, Vortex80AEsc)
{
    logic::motors::Vortex80AEsc vortex {drivers.pwm, pwmData, data::motors::Directionality::UNIDIRECTIONAL};

    EXPECT_DOUBLE_EQ(vortex.calculateDutyCycle(0.0), 0.5);
    EXPECT_DOUBLE_EQ(vortex.calculateDutyCycle(0.50), 0.75);
    EXPECT_DOUBLE_EQ(vortex.calculateDutyCycle(1.0), 1.0);
}