#include "gtest/gtest.h"
#include "abstractmecanumcalculator.hpp"
#include "quaddrivedata.hpp"
#include "chassislogicaliases.hpp"
#include <iostream>

using Calculator = logic::chassis::AbstractMecanumCalculator;
Calculator calc{};
using QuadDriveData = data::chassis::QuadDriveData<double>;
using Translation2D = logic::chassis::Translation2D;

TEST(forwardTest, baseMecanumMotionCalculator )
{

    const QuadDriveData test{1.0,1.0,1.0,1.0};
    const Translation2D forwardTestExpectedMotion{0.0, 1.0};
    calc.setQuadDriveData(test);
    std::cout << calc.getTranslation().x;
    EXPECT_DOUBLE_EQ(calc.getTranslation().x, forwardTestExpectedMotion.x);
    EXPECT_DOUBLE_EQ(calc.getTranslation().y, forwardTestExpectedMotion.y);
}

TEST(leftTest, baseMecanumMotionCalculator )
{

    const QuadDriveData test{1.0,-1.0,-1.0,1.0};
    const Translation2D expectedMotion{1.0, 0.0};
    calc.setQuadDriveData(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x, expectedMotion.x);
    EXPECT_DOUBLE_EQ(calc.getTranslation().y, expectedMotion.y);
}

TEST(zeroTest, baseMecanumMotionCalculator )
{

    const QuadDriveData test{0,0,0,0};
    const Translation2D expectedMotion{0.0, 0.0};
    calc.setQuadDriveData(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x, expectedMotion.x);
    EXPECT_DOUBLE_EQ(calc.getTranslation().y, expectedMotion.y);
}

TEST(clockwiseOffset, baseMecanumMotionCalculator )
{

    const QuadDriveData test{-1,1,-1,1};
    const double expectedOffset{1};
    calc.setQuadDriveData(test);
    EXPECT_DOUBLE_EQ(calc.getRotationalOffset(), expectedOffset);
}