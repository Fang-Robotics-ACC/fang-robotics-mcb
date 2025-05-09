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
class FieldMecanumParameterTest : public ::testing::TestWithParam<std::tuple<logic::chassis::Velocity2D, RPM, Radians, Meters, Meters, Meters>>
{
protected:
};

TEST_P(FieldMecanumParameterTest, translationRotationTests)
{
    //The field mecanum logic must have it translation and rotation result in
    //Wheel speeds which conform to the inverse kinematics :)
    const logic::chassis::Velocity2D translation{std::get<0>(GetParam())};
    const RPM rotation{std::get<1>(GetParam())};
    const Radians robotAngle{std::get<2>(GetParam())};
    const Meters horizontalDistance{std::get<3>(GetParam())};
    const Meters verticalDistance{std::get<4>(GetParam())};
    const Meters wheelRadius{std::get<5>(GetParam())};

    logic::chassis::MecanumCalculator mecanumCalc{horizontalDistance, verticalDistance, wheelRadius};
    logic::chassis::FieldMecanumLogic mecanumLogic{horizontalDistance, verticalDistance, wheelRadius};
    mathAliases::AbstractVector2D strippedTranslation{translation.x.to<double>(), translation.y.to<double>()};
    //Transform velocity relative to robot
    mathAliases::AbstractVector2D strippedRobotTranslation{util::math::rotateVector2D(strippedTranslation, -robotAngle)};
    logic::chassis::Velocity2D expectedRobotTranslation{MetersPerSecond{strippedRobotTranslation.x}, MetersPerSecond{strippedRobotTranslation.y}};

    mecanumLogic.setTotalMotion(translation, rotation, robotAngle);
    mecanumCalc.setWheelSpeeds(mecanumLogic.getWheelSpeeds());
    const logic::chassis::Velocity2D outputTranslation{mecanumCalc.getTranslation()};
    const RPM outputRotation{mecanumCalc.getRotation()};

    EXPECT_DOUBLE_EQ(outputTranslation.x.to<double>(), expectedRobotTranslation.x.to<double>());
    EXPECT_DOUBLE_EQ(outputTranslation.y.to<double>(), expectedRobotTranslation.y.to<double>());
    EXPECT_DOUBLE_EQ(outputRotation.to<double>(), rotation.to<double>());
}

INSTANTIATE_TEST_SUITE_P(zeroTest, FieldMecanumParameterTest,
                         testing::Values(std::make_tuple(logic::chassis::Velocity2D{0_mps, 0_mps}, 0_rpm, 0_rad, 1_m, 1_m, 1_m)));

INSTANTIATE_TEST_SUITE_P(yTranslationTest, FieldMecanumParameterTest,
                         testing::Values(std::make_tuple(logic::chassis::Velocity2D{0_mps, 234.23_mps}, 0_rpm, 0_rad, 1_m, 1_m, 1_m),
                                         std::make_tuple(logic::chassis::Velocity2D{0_mps, -234_mps}, 0_rpm, 0_rad, 1_m, 1_m, 1_m),
                                         std::make_tuple(logic::chassis::Velocity2D{0_mps, 12_mps}, 0_rpm, 0_rad, 1_m, 2_m, 4_m),
                                         std::make_tuple(logic::chassis::Velocity2D{0_mps, -235.45_mps}, 0_rpm, 0_rad, 2_m, 1_m, 5.5_m)));

INSTANTIATE_TEST_SUITE_P(xTranslationTest, FieldMecanumParameterTest,
                         testing::Values(std::make_tuple(logic::chassis::Velocity2D{234.23_mps, 0.0_mps}, 0_rpm, 0_rad, 1_m, 1_m, 1_m),
                                         std::make_tuple(logic::chassis::Velocity2D{12.23_mps, 0.0_mps}, 0_rpm, 0_rad, 1_m, 1_m, 1_m),
                                         std::make_tuple(logic::chassis::Velocity2D{234_mps, 0.0_mps}, 0_rpm, 0_rad, 2_m, 1_m, 4_m),
                                         std::make_tuple(logic::chassis::Velocity2D{123.2_mps, 0.0_mps}, 0_rpm, 0_rad, 1_m, 3_m, 5.5_m)));

INSTANTIATE_TEST_SUITE_P(rotationTest, FieldMecanumParameterTest,
                         testing::Values(std::make_tuple(logic::chassis::Velocity2D{0.0_mps, 0.0_mps}, 4_rpm, 0_rad, 1_m, 1_m, 1_m),
                                         std::make_tuple(logic::chassis::Velocity2D{0.0_mps, 0.0_mps}, -234_rpm, 0_rad, 1_m, 1_m, 1_m),
                                         std::make_tuple(logic::chassis::Velocity2D{0.0_mps, 0.0_mps}, 1.23_rpm, 0_rad, 2_m, 1_m, 4_m),
                                         std::make_tuple(logic::chassis::Velocity2D{0.0_mps, 0.0_mps}, 5_rpm, 0_rad, 1_m, 3_m, 5.5_m)));

INSTANTIATE_TEST_SUITE_P(fieldAngleTest, FieldMecanumParameterTest,
                         testing::Values(std::make_tuple(logic::chassis::Velocity2D{1.0_mps, 0.0_mps}, 0.0_rpm, 90_deg, 1_m, 1_m, 1_m),
                                         std::make_tuple(logic::chassis::Velocity2D{0.0_mps, 1.0_mps}, 0.0_rpm, 10_rad, 1_m, 1_m, 1_m),
                                         std::make_tuple(logic::chassis::Velocity2D{-23.0_mps, -2340.0_mps}, 0.0_rpm, 4353_rad, 2_m, 1_m, 4_m),
                                         std::make_tuple(logic::chassis::Velocity2D{34.0_mps, 0.0_mps}, 0.0_rpm, -234_rad, 1_m, 3_m, 5.5_m)));