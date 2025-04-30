#include "gtest/gtest.h"
#include "basemecanummotioncalculator.h"
#include "quaddrivedata.h"
#include "chassislogicaliases.h"
#include <iostream>

TEST(mecanumCalculator, mecanumLogic)
{
    using Calculator = logic::chassis::BaseMecanumMotionCalculator;
    Calculator calc{};
    using QuadDriveData = data::chassis::QuadDriveData<double>;
    using Translation2D = logic::chassis::Translation2D;

    const QuadDriveData forwardTest{1.0,1.0,1.0,1.0};
    const Translation2D forwardTestExpectedMotion{0.0, 1.0};
    calc.setQuadDriveData(forwardTest);
    std::cout << calc.getTranslation().x;
    EXPECT_DOUBLE_EQ(calc.getTranslation().x, forwardTestExpectedMotion.x);
    EXPECT_DOUBLE_EQ(calc.getTranslation().y, forwardTestExpectedMotion.y);
}