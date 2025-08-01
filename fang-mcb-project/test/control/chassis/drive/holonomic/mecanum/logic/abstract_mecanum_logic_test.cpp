#include "control/chassis/drive/holonomic/mecanum/logic/abstract_mecanum_calculator.hpp"
#include "control/chassis/drive/holonomic/mecanum/logic/abstract_robot_mecanum_logic.hpp"

#include <gtest/gtest.h>
#include <iostream>

using namespace fang;
using Calculator = chassis::AbstractMecanumCalculator;
using Logic = chassis::AbstractRobotMecanumLogic;
using Translation2D = chassis::AbstractVelocity2D;

//Todo: Add intermediate test cases

TEST(ZeroTest, RobotMecanumLogic)
{
    Calculator calc{};
    Logic robotMecanum{};
    robotMecanum.setMotion(Translation2D{0.0, 0.0}, 0.0);
    Translation2D expectedTranslation{0.0, 0.0};
    double expectedRotationOffset{0.0};
    calc.setWheelSpeeds(robotMecanum.getWheelSpeeds());
    EXPECT_DOUBLE_EQ(calc.getTranslation().x, expectedTranslation.x);
    EXPECT_DOUBLE_EQ(calc.getTranslation().y, expectedTranslation.y);
    EXPECT_DOUBLE_EQ(calc.getRotationOffset(), expectedRotationOffset);
}

TEST(ForwardTest, RobotMecanumLogic)
{
    Calculator calc{};
    Logic robotMecanum{};
    robotMecanum.setMotion(Translation2D{0.0, 1.0}, 0.0);
    Translation2D expectedTranslation{0.0, 1.0};
    double expectedRotationOffset{0.0};
    calc.setWheelSpeeds(robotMecanum.getWheelSpeeds());
    EXPECT_DOUBLE_EQ(calc.getTranslation().x, expectedTranslation.x);
    EXPECT_DOUBLE_EQ(calc.getTranslation().y, expectedTranslation.y);
    EXPECT_DOUBLE_EQ(calc.getRotationOffset(), expectedRotationOffset);
}

TEST(LateralTest, RobotMecanumLogic)
{
    Calculator calc{};
    Logic robotMecanum{};
    Translation2D expectedTranslation{0.0, 1.0};
    double expectedRotationOffset{0.0};

    robotMecanum.setMotion(expectedTranslation, expectedRotationOffset);

    calc.setWheelSpeeds(robotMecanum.getWheelSpeeds());
    EXPECT_DOUBLE_EQ(calc.getTranslation().x, expectedTranslation.x);
    EXPECT_DOUBLE_EQ(calc.getTranslation().y, expectedTranslation.y);
    EXPECT_DOUBLE_EQ(calc.getRotationOffset(), expectedRotationOffset);
}

TEST(RotationTest, RobotMecanumLogic)
{
    Calculator calc{};
    Logic robotMecanum{};
    Translation2D expectedTranslation{0.0, 0.0};
    double expectedRotationOffset{10.0};

    robotMecanum.setMotion(expectedTranslation, expectedRotationOffset);

    calc.setWheelSpeeds(robotMecanum.getWheelSpeeds());
    EXPECT_DOUBLE_EQ(calc.getTranslation().x, expectedTranslation.x);
    EXPECT_DOUBLE_EQ(calc.getTranslation().y, expectedTranslation.y);
    EXPECT_DOUBLE_EQ(calc.getRotationOffset(), expectedRotationOffset);
}

TEST(CombinedTest1, RobotMecanumLogic)
{
    Calculator calc{};
    Logic robotMecanum{};
    Translation2D expectedTranslation{2.234, -2.23};
    double expectedRotationOffset{20.0};

    robotMecanum.setMotion(expectedTranslation, expectedRotationOffset);

    calc.setWheelSpeeds(robotMecanum.getWheelSpeeds());
    EXPECT_DOUBLE_EQ(calc.getTranslation().x, expectedTranslation.x);
    EXPECT_DOUBLE_EQ(calc.getTranslation().y, expectedTranslation.y);
    EXPECT_DOUBLE_EQ(calc.getRotationOffset(), expectedRotationOffset);
}


