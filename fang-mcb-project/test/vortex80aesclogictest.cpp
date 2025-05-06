#include <gtest/gtest.h>
#include "vortex80aesclogic.hpp"
#include "unitaliases.hpp"

TEST(zeroTest, Vortex80AEscLogic)
{
    //2 ms period
    const Hertz standardFrequency{500};
    logic::motors::Vortex80AEscLogic vortex {};

    EXPECT_DOUBLE_EQ(vortex.adaptedDutyCycle(0.0, standardFrequency), 0.5);
}

TEST(midRangeTest, Vortex80AEscLogic)
{
    //2 ms period
    const Hertz standardFrequency{500};
    logic::motors::Vortex80AEscLogic vortex {};

    EXPECT_DOUBLE_EQ(vortex.adaptedDutyCycle(0.5, standardFrequency), 0.75);
}

TEST(fullRangeTest, Vortex80AEscLogic)
{
    //2 ms period
    const Hertz standardFrequency{500};
    logic::motors::Vortex80AEscLogic vortex {};

    EXPECT_DOUBLE_EQ(vortex.adaptedDutyCycle(1, standardFrequency), 1.0);
}

TEST(oddRangeTest, Vortex80AEscLogic)
{
    //4 ms period
    const Hertz nonStandardFrequency{250};
    logic::motors::Vortex80AEscLogic vortex {};

    EXPECT_DOUBLE_EQ(vortex.adaptedDutyCycle(1, nonStandardFrequency), 0.5);
}

TEST(bidirectionalTest, Vortex80AEscLogic)
{
    logic::motors::Vortex80AEscLogic vortex {data::motors::Directionality::BIDIRECTIONAL};

    EXPECT_DOUBLE_EQ(vortex.calculateDutyCycle(-1.0), 0.5);
    EXPECT_DOUBLE_EQ(vortex.calculateDutyCycle(0.0), 0.75);
    EXPECT_DOUBLE_EQ(vortex.calculateDutyCycle(1.0), 1.0);
}

TEST(unidirectionalTest, Vortex80AEscLogic)
{
    logic::motors::Vortex80AEscLogic vortex {data::motors::Directionality::UNIDIRECTIONAL};

    EXPECT_DOUBLE_EQ(vortex.calculateDutyCycle(0.0), 0.5);
    EXPECT_DOUBLE_EQ(vortex.calculateDutyCycle(0.50), 0.75);
    EXPECT_DOUBLE_EQ(vortex.calculateDutyCycle(1.0), 1.0);
}