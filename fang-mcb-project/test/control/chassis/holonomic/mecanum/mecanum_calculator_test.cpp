#include "control/chassis/holonomic/mecanum/logic/mecanum_calculator.hpp"
#include "unitaliases.hpp"

#include <gtest/gtest.h>
#include <iostream>

TEST(mecanumCalculator, forwardsTest)
{
    using namespace units::literals;
    {
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const chassis::WheelSpeeds test {1.0_rad_per_s, 1.0_rad_per_s, 1.0_rad_per_s, 1.0_rad_per_s};
    const chassis::Velocity2D expected{0.0_mps, 1.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }

    {
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 4.0_m};
    const chassis::WheelSpeeds test {1.0_rad_per_s, 1.0_rad_per_s, 1.0_rad_per_s, 1.0_rad_per_s};
    const chassis::Velocity2D expected{0.0_mps, 4.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }

    {
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const chassis::WheelSpeeds test {1.5_rad_per_s, 1.5_rad_per_s, 1.5_rad_per_s, 1.5_rad_per_s};
    const chassis::Velocity2D expected{0.0_mps, 1.5_mps};
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
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const chassis::WheelSpeeds test {-1.0_rad_per_s, -1.0_rad_per_s, -1.0_rad_per_s, -1.0_rad_per_s};
    const chassis::Velocity2D expected{0.0_mps, -1.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }

    {
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 4.0_m};
    const chassis::WheelSpeeds test {-1.0_rad_per_s, -1.0_rad_per_s, -1.0_rad_per_s, -1.0_rad_per_s};
    const chassis::Velocity2D expected{0.0_mps, -4.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
    //Decimal test
    {
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const chassis::WheelSpeeds test {-1000.534_rad_per_s, -1000.534_rad_per_s, -1000.534_rad_per_s, -1000.534_rad_per_s};
    const chassis::Velocity2D expected{0.0_mps, -1000.534_mps};
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
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const chassis::WheelSpeeds test {1.0_rad_per_s, -1.0_rad_per_s, -1.0_rad_per_s, 1.0_rad_per_s};
    const chassis::Velocity2D expected{1.0_mps, 0.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }

    //Wheel size test
    {
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 4.0_m};
    const chassis::WheelSpeeds test {1.0_rad_per_s, -1.0_rad_per_s, -1.0_rad_per_s, 1.0_rad_per_s};
    const chassis::Velocity2D expected{4.0_mps, 0.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
    //Decimal test
    {
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const chassis::WheelSpeeds test {1000.534_rad_per_s, -1000.534_rad_per_s, -1000.534_rad_per_s, 1000.534_rad_per_s};
    const chassis::Velocity2D expected{1000.534_mps, 0.0_mps};
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
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const chassis::WheelSpeeds test {-1.0_rad_per_s, 1.0_rad_per_s, 1.0_rad_per_s, -1.0_rad_per_s};
    const chassis::Velocity2D expected{-1.0_mps, 0.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }

    //Wheel size test
    {
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 4.0_m};
    const chassis::WheelSpeeds test {-1.0_rad_per_s, 1.0_rad_per_s, 1.0_rad_per_s, -1.0_rad_per_s};
    const chassis::Velocity2D expected{-4.0_mps, 0.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
    //Decimal test
    {
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const chassis::WheelSpeeds test {-1000.534_rad_per_s, 1000.534_rad_per_s, 1000.534_rad_per_s, -1000.534_rad_per_s};
    const chassis::Velocity2D expected{-1000.534_mps, 0.0_mps};
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
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const chassis::WheelSpeeds test {-1.0_rad_per_s, 1.0_rad_per_s, -1.0_rad_per_s, 1.0_rad_per_s};
    const chassis::Velocity2D expected{0.0_mps, 0.0_mps};
    const RPM expectedRotation{1.0_rad_per_s};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }

    //Wheel size test
    {
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 4.0_m};
    const chassis::WheelSpeeds test {-1.0_rad_per_s, 1.0_rad_per_s, -1.0_rad_per_s, 1.0_rad_per_s};
    const chassis::Velocity2D expected{0.0_mps, 0.0_mps};
    const RPM expectedRotation{4.0_rad_per_s};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
    //Different chassis size test
     {
    chassis::MecanumCalculator calc{2.0_m, 2.0_m, 1.0_m};
    const chassis::WheelSpeeds test {-1.0_rad_per_s, 1.0_rad_per_s, -1.0_rad_per_s, 1.0_rad_per_s};
    const chassis::Velocity2D expected{0.0_mps, 0.0_mps};
    const RPM expectedRotation{0.5_rad_per_s};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
}

TEST(clockwiseTest, MecanumMotionCalculator)
{
    using namespace units::literals;
    {
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const chassis::WheelSpeeds test {1.0_rad_per_s, -1.0_rad_per_s, 1.0_rad_per_s, -1.0_rad_per_s};
    const chassis::Velocity2D expected{0.0_mps, 0.0_mps};
    const RPM expectedRotation{-1.0_rad_per_s};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }

    //Wheel size test
    {
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 4.0_m};
    const chassis::WheelSpeeds test {1.0_rad_per_s, -1.0_rad_per_s, 1.0_rad_per_s, -1.0_rad_per_s};
    const chassis::Velocity2D expected{0.0_mps, 0.0_mps};
    const RPM expectedRotation{-4.0_rad_per_s};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }

    //Different chassis size test
    {
    chassis::MecanumCalculator calc{2.0_m, 2.0_m, 1.0_m};
    const chassis::WheelSpeeds test {1.0_rad_per_s, -1.0_rad_per_s, 1.0_rad_per_s, -1.0_rad_per_s};
    const chassis::Velocity2D expected{0.0_mps, 0.0_mps};
    const RPM expectedRotation{-0.5_rad_per_s};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
    //Different chassis size test
    {
    chassis::MecanumCalculator calc{1.0_m, 3.0_m, 1.0_m};
    const chassis::WheelSpeeds test {1.0_rad_per_s, -1.0_rad_per_s, 1.0_rad_per_s, -1.0_rad_per_s};
    const chassis::Velocity2D expected{0.0_mps, 0.0_mps};
    const RPM expectedRotation{-0.5_rad_per_s};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
}

TEST(zeroTest, MecanumMotionCalculator)
{
    using namespace units::literals;
    {
    chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const chassis::WheelSpeeds test {0.0_rad_per_s, 0.0_rad_per_s, 0.0_rad_per_s, 0.0_rad_per_s};
    const chassis::Velocity2D expected{0.0_mps, 0.0_mps};
    const RPM expectedRotation{0.0_rad_per_s};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
    }
}

