#include "gtest/gtest.h"
#include "abstractmecanumcalculator.hpp"
#include "abstractrobotmecanumlogic.hpp"
#include "quaddrivedata.hpp"
#include "chassislogicaliases.hpp"
#include <iostream>

using Calculator = logic::chassis::AbstractMecanumCalculator;
using Logic = logic::chassis::AbstractRobotMecanumLogic;
using QuadDriveData = data::chassis::QuadDriveData<double>;
using Translation2D = logic::chassis::Translation2D;



TEST(ForwardTest, RobotMecanumLogic)
{
    Calculator calc{};
    Logic robotMecanum{};
    robotMecanum.setMotion(Translation2D{0.0, 0.0}, 0.0);
    Translation2D expectedTranslation{1.0, 0.0};
    double expectedRotationOffset{0.0};
    calc.setQuadDriveData(robotMecanum.getWheelSpeeds());
    EXPECT_DOUBLE_EQ(calc.getTranslation().x, expectedTranslation.x);
    EXPECT_DOUBLE_EQ(calc.getTranslation().y, expectedTranslation.y);
    EXPECT_DOUBLE_EQ(calc.getRotationOffset(), expectedRotationOffset);
}