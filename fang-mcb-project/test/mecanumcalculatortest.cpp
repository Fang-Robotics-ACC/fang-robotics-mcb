#include "gtest/gtest.h"
#include "mecanumcalculator.hpp"
#include "unitaliases.hpp"
#include "quaddrivedata.hpp"
#include "chassislogicaliases.hpp"
#include <iostream>

TEST(mecanumCalculator, forwardsTest)
{
    using namespace units::literals;
    {
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const logic::chassis::QuadDriveData test {1.0_rpm, 1.0_rpm, 1.0_rpm, 1.0_rpm};
    const logic::chassis::Velocity2D expected{0.0_mps, 1.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }

    {
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 4.0_m};
    const logic::chassis::QuadDriveData test {1.0_rpm, 1.0_rpm, 1.0_rpm, 1.0_rpm};
    const logic::chassis::Velocity2D expected{0.0_mps, 4.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }

    {
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const logic::chassis::QuadDriveData test {1.5_rpm, 1.5_rpm, 1.5_rpm, 1.5_rpm};
    const logic::chassis::Velocity2D expected{0.0_mps, 1.5_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
}

TEST(backwardsTest, MecanumMotionCalculator )
{
    using namespace units::literals;
    {
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const logic::chassis::QuadDriveData test {-1.0_rpm, -1.0_rpm, -1.0_rpm, -1.0_rpm};
    const logic::chassis::Velocity2D expected{0.0_mps, -1.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }

    {
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 4.0_m};
    const logic::chassis::QuadDriveData test {-1.0_rpm, -1.0_rpm, -1.0_rpm, -1.0_rpm};
    const logic::chassis::Velocity2D expected{0.0_mps, -4.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
    //Decimal test
    {
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const logic::chassis::QuadDriveData test {-1000.534_rpm, -1000.534_rpm, -1000.534_rpm, -1000.534_rpm};
    const logic::chassis::Velocity2D expected{0.0_mps, -1000.534_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
}

TEST(rightTesst, MecanumMotionCalculator )
{
    using namespace units::literals;
    {
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const logic::chassis::QuadDriveData test {1.0_rpm, -1.0_rpm, -1.0_rpm, 1.0_rpm};
    const logic::chassis::Velocity2D expected{1.0_mps, 0.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }

    //Wheel size test
    {
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 4.0_m};
    const logic::chassis::QuadDriveData test {1.0_rpm, -1.0_rpm, -1.0_rpm, 1.0_rpm};
    const logic::chassis::Velocity2D expected{4.0_mps, 0.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
    //Decimal test
    {
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const logic::chassis::QuadDriveData test {1000.534_rpm, -1000.534_rpm, -1000.534_rpm, 1000.534_rpm};
    const logic::chassis::Velocity2D expected{1000.534_mps, 0.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
}

TEST(leftTest, MecanumMotionCalculator)
{
    using namespace units::literals;
    {
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const logic::chassis::QuadDriveData test {-1.0_rpm, 1.0_rpm, 1.0_rpm, -1.0_rpm};
    const logic::chassis::Velocity2D expected{-1.0_mps, 0.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }

    //Wheel size test
    {
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 4.0_m};
    const logic::chassis::QuadDriveData test {-1.0_rpm, 1.0_rpm, 1.0_rpm, -1.0_rpm};
    const logic::chassis::Velocity2D expected{-4.0_mps, 0.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
    //Decimal test
    {
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const logic::chassis::QuadDriveData test {-1000.534_rpm, 1000.534_rpm, 1000.534_rpm, -1000.534_rpm};
    const logic::chassis::Velocity2D expected{-1000.534_mps, 0.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
}

TEST(counterClockwiseTest, MecanumMotionCalculator)
{
    using namespace units::literals;
    {
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const logic::chassis::QuadDriveData test {-1.0_rpm, 1.0_rpm, -1.0_rpm, 1.0_rpm};
    const logic::chassis::Velocity2D expected{0.0_mps, 0.0_mps};
    const RPM expectedRotation{1.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }

    //Wheel size test
    {
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 4.0_m};
    const logic::chassis::QuadDriveData test {-1.0_rpm, 1.0_rpm, -1.0_rpm, 1.0_rpm};
    const logic::chassis::Velocity2D expected{0.0_mps, 0.0_mps};
    const RPM expectedRotation{4.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
    //Different chassis size test
     {
    logic::chassis::MecanumCalculator calc{2.0_m, 2.0_m, 1.0_m};
    const logic::chassis::QuadDriveData test {-1.0_rpm, 1.0_rpm, -1.0_rpm, 1.0_rpm};
    const logic::chassis::Velocity2D expected{0.0_mps, 0.0_mps};
    const RPM expectedRotation{0.5};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
}