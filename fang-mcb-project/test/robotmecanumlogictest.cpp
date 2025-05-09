#include "gtest/gtest.h"
#include "unitaliases.hpp"
#include "chassislogicaliases.hpp"
#include "robotmecanumlogic.hpp"
#include "mecanumcalculator.hpp"

#include <iostream>

TEST(zeroTest, robotMecanumLogic)
{
    {
        using namespace units::literals;
        const Meters horizontalWheelDistance{1};
        const Meters verticalWheelDistance{1};
        const Meters wheelRadius{1};

        const logic::chassis::Velocity2D translation{0.0_mps, 0.0_mps};
        const RPM rotation{0.0};

        logic::chassis::RobotMecanumLogic mecanumLogic{horizontalWheelDistance, verticalWheelDistance, wheelRadius};
        logic::chassis::MecanumCalculator mecanumCalc{horizontalWheelDistance, verticalWheelDistance, wheelRadius};

        mecanumLogic.setTranslation(translation);
        mecanumLogic.setRotation(rotation);

        mecanumCalc.setWheelSpeeds(mecanumLogic.getWheelSpeeds());

        const logic::chassis::Velocity2D outputTranslation{mecanumCalc.getTranslation()};
        const RPM outputRotation{mecanumCalc.getRotation()};

        EXPECT_DOUBLE_EQ(translation.x.to<double>(), outputTranslation.x.to<double>());
        EXPECT_DOUBLE_EQ(translation.y.to<double>(), outputTranslation.y.to<double>());
        EXPECT_DOUBLE_EQ(rotation.to<double>(), outputRotation.to<double>());
    }
}

TEST(forwardTest, robotMecanumLogic)
{
    //Base case
    {
        using namespace units::literals;
        const Meters horizontalWheelDistance{1};
        const Meters verticalWheelDistance{1};
        const Meters wheelRadius{1};

        const logic::chassis::Velocity2D translation{0.0_mps, 1.0_mps};
        const RPM rotation{0.0};

        logic::chassis::RobotMecanumLogic mecanumLogic{horizontalWheelDistance, verticalWheelDistance, wheelRadius};
        logic::chassis::MecanumCalculator mecanumCalc{horizontalWheelDistance, verticalWheelDistance, wheelRadius};

        mecanumLogic.setTranslation(translation);
        mecanumLogic.setRotation(rotation);

        mecanumCalc.setWheelSpeeds(mecanumLogic.getWheelSpeeds());

        const logic::chassis::Velocity2D outputTranslation{mecanumCalc.getTranslation()};
        const RPM outputRotation{mecanumCalc.getRotation()};

        std::cout << mecanumLogic.getFrontLeftWheelSpeed();
        std::cout << mecanumLogic.getFrontLeftWheelSpeed().name();
        EXPECT_DOUBLE_EQ(translation.x.to<double>(), outputTranslation.x.to<double>());
        EXPECT_DOUBLE_EQ(translation.y.to<double>(), outputTranslation.y.to<double>());
        EXPECT_DOUBLE_EQ(rotation.to<double>(), outputRotation.to<double>());
    }

    //Different wheel radius case
    {
        using namespace units::literals;
        const Meters horizontalWheelDistance{1};
        const Meters verticalWheelDistance{1};
        const Meters wheelRadius{4};

        const logic::chassis::Velocity2D translation{0.0_mps, 1.0_mps};
        const RPM rotation{0.0};

        logic::chassis::RobotMecanumLogic mecanumLogic{horizontalWheelDistance, verticalWheelDistance, wheelRadius};
        logic::chassis::MecanumCalculator mecanumCalc{horizontalWheelDistance, verticalWheelDistance, wheelRadius};

        mecanumLogic.setTranslation(translation);
        mecanumLogic.setRotation(rotation);

        mecanumCalc.setWheelSpeeds(mecanumLogic.getWheelSpeeds());

        const logic::chassis::Velocity2D outputTranslation{mecanumCalc.getTranslation()};
        const RPM outputRotation{mecanumCalc.getRotation()};

        EXPECT_DOUBLE_EQ(translation.x.to<double>(), outputTranslation.x.to<double>());
        EXPECT_DOUBLE_EQ(translation.y.to<double>(), outputTranslation.y.to<double>());
        EXPECT_DOUBLE_EQ(rotation.to<double>(), outputRotation.to<double>());
    }

    //Random number case
    {
        using namespace units::literals;
        const Meters horizontalWheelDistance{1};
        const Meters verticalWheelDistance{1};
        const Meters wheelRadius{4};

        const logic::chassis::Velocity2D translation{0.0_mps, 234.28929_mps};
        const RPM rotation{0.0};

        logic::chassis::RobotMecanumLogic mecanumLogic{horizontalWheelDistance, verticalWheelDistance, wheelRadius};
        logic::chassis::MecanumCalculator mecanumCalc{horizontalWheelDistance, verticalWheelDistance, wheelRadius};

        mecanumLogic.setTranslation(translation);
        mecanumLogic.setRotation(rotation);

        mecanumCalc.setWheelSpeeds(mecanumLogic.getWheelSpeeds());

        const logic::chassis::Velocity2D outputTranslation{mecanumCalc.getTranslation()};
        const RPM outputRotation{mecanumCalc.getRotation()};

        EXPECT_DOUBLE_EQ(translation.x.to<double>(), outputTranslation.x.to<double>());
        EXPECT_DOUBLE_EQ(translation.y.to<double>(), outputTranslation.y.to<double>());
        EXPECT_DOUBLE_EQ(rotation.to<double>(), outputRotation.to<double>());
    }
}