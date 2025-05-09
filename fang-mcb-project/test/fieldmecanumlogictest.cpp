#include "gtest/gtest.h"
#include "fieldmecanumlogic.hpp"
#include "mecanumcalculator.hpp"
#include "chassislogicaliases.hpp"
#include "rotatevector2d.hpp"
#include "mathaliases.hpp"
#include "unitaliases.hpp"
#include <tuple>

using namespace units::literals;
//Input velocity, expected velocigty
//Input angular velocity, expected angular velocity,
//robot angle Horizontal Distance, Vertical Distance, Wheel Radius
class FieldMecanumParameterTest : public ::testing::TestWithParam<std::tuple<logic::chassis::Velocity2D, logic::chassis::Velocity2D, RPM, RPM, Radians, Meters, Meters, Meters>>
{
protected:
};

TEST_P(FieldMecanumParameterTest, translationRotationTests)
{
    //The field mecanum logic must have it translation and rotation result in
    //Wheel speeds which conform to the inverse kinematics :)
    const logic::chassis::Velocity2D translation{std::get<0>(GetParam())};
    const logic::chassis::Velocity2D expectedTranslation{std::get<1>(GetParam())};
    const RPM rotation{std::get<2>(GetParam())};
    const RPM expectedRotation{std::get<3>(GetParam())};
    const Radians robotAngle{std::get<4>(GetParam())};
    const Meters horizontalDistance{std::get<5>(GetParam())};
    const Meters verticalDistance{std::get<6>(GetParam())};
    const Meters wheelRadius{std::get<7>(GetParam())};

    logic::chassis::MecanumCalculator mecanumCalc{horizontalDistance, verticalDistance, wheelRadius};
    logic::chassis::FieldMecanumLogic mecanumLogic{horizontalDistance, verticalDistance, wheelRadius};
    mathAliases::AbstractVector2D strippedTranslation{expectedTranslation.x.to<double>(), expectedTranslation.y.to<double>()};
    //Transform velocity relative to robot
    mathAliases::AbstractVector2D strippedRobotTranslation{util::math::rotateVector2D(strippedTranslation, robotAngle)};
    logic::chassis::Velocity2D expectedRobotTranslation{MetersPerSecond{strippedRobotTranslation.x}, MetersPerSecond{strippedRobotTranslation.y}};

    mecanumLogic.setTotalMotion(translation, rotation, robotAngle);
    mecanumCalc.setWheelSpeeds(mecanumLogic.getWheelSpeeds());
    const logic::chassis::Velocity2D outputTranslation{mecanumCalc.getTranslation()};
    const RPM outputRotation{mecanumCalc.getRotation()};

    EXPECT_DOUBLE_EQ(outputTranslation.x.to<double>(), expectedRobotTranslation.x.to<double>());
    EXPECT_DOUBLE_EQ(outputTranslation.y.to<double>(), expectedRobotTranslation.y.to<double>());
    EXPECT_DOUBLE_EQ(outputRotation.to<double>(), expectedRotation.to<double>());
}

INSTANTIATE_TEST_SUITE_P(zeroTest, FieldMecanumParameterTest,
                         testing::Values(std::make_tuple(logic::chassis::Velocity2D{0_mps, 0_mps}, logic::chassis::Velocity2D{0_mps, 0_mps},
                                                         0_rpm, 0_rpm, 0_rad, 1_m, 1_m, 1_m)));

INSTANTIATE_TEST_SUITE_P(yTranslationTest, FieldMecanumParameterTest,
                         testing::Values(std::make_tuple(logic::chassis::Velocity2D{0_mps, 1_mps}, logic::chassis::Velocity2D{0_mps, 1_mps},
                                                         0_rpm, 0_rpm, 0_rad, 1_m, 1_m, 1_m)));