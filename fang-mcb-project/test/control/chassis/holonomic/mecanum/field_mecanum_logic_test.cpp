#include "gtest/gtest.h"
#include "control/chassis/holonomic/mecanum/logic/field_mecanum_logic.hpp"
#include "control/chassis/holonomic/mecanum/logic/mecanum_calculator.hpp"
#include "util/math/geometry/rotate_vector_2d.hpp"
#include "chassislogicaliases.hpp"
#include "mathaliases.hpp"
#include "unitaliases.hpp"
#include <tuple>

//The vector rotaiton function is within an accuracy of 1e-14 (14 decimal places)
//The error tends to be at around 1e-13, which is still reasonable (13 decimal places)
constexpr double k_tolerance{1e-12};

//The error was detected in the field angle tests when despite 0 rotation being specified, the resulting rotation was arou

using namespace units::literals;
//Input velocity, expected velocigty
//Input angular velocity, expected angular velocity,
//robot angle Horizontal Distance, Vertical Distance, Wheel Radius
class FieldMecanumParameterTest : public ::testing::TestWithParam<std::tuple<chassis::Velocity2D, RPM, Radians, Meters, Meters, Meters>>
{
protected:
};

TEST_P(FieldMecanumParameterTest, translationRotationTests)
{
    //The field mecanum logic must have it translation and rotation result in
    //Wheel speeds which conform to the inverse kinematics :)
    const chassis::Velocity2D translation{std::get<0>(GetParam())};
    const RPM rotation{std::get<1>(GetParam())};
    const Radians robotAngle{std::get<2>(GetParam())};
    const Meters horizontalDistance{std::get<3>(GetParam())};
    const Meters verticalDistance{std::get<4>(GetParam())};
    const Meters wheelRadius{std::get<5>(GetParam())};
    

    chassis::MecanumCalculator mecanumCalc{horizontalDistance, verticalDistance, wheelRadius};
    chassis::FieldMecanumLogic mecanumLogic{horizontalDistance, verticalDistance, wheelRadius};
    math::AbstractVector2D strippedTranslation{translation.x.to<double>(), translation.y.to<double>()};
    //Transform velocity relative to robot
    math::AbstractVector2D strippedRobotTranslation{math::rotateVector2D(strippedTranslation, -robotAngle)};
    chassis::Velocity2D expectedRobotTranslation{MetersPerSecond{strippedRobotTranslation.x}, MetersPerSecond{strippedRobotTranslation.y}};

    mecanumLogic.setTotalMotion(translation, rotation, robotAngle);
    //Ensure getters work properly
    EXPECT_TRUE(mecanumLogic.getTranslation().x == translation.x);
    EXPECT_TRUE(mecanumLogic.getTranslation().y == translation.y);
    //RPM to Radians Per Second conversion introduces floating point errors
    EXPECT_NEAR(mecanumLogic.getRotation().to<double>(), rotation.to<double>(), k_tolerance);

    mecanumCalc.setWheelSpeeds(mecanumLogic.getWheelSpeeds());
    chassis::Velocity2D outputTranslation{mecanumCalc.getTranslation()};
    RPM outputRotation{mecanumCalc.getRotation()};

    EXPECT_NEAR(outputTranslation.x.to<double>(), expectedRobotTranslation.x.to<double>(), k_tolerance);
    EXPECT_NEAR(outputTranslation.y.to<double>(), expectedRobotTranslation.y.to<double>(), k_tolerance);
    EXPECT_NEAR(outputRotation.to<double>(), rotation.to<double>(), k_tolerance);

    //The implementation of setting the angle with setRobotAngle versus total motion is different
    //It calls setTranslation to reset the translation stored in the robot centric logic to the new angle
    //setTotalMotion calls a private function rawSetRobotAngle which does not adjust the translation; however,
    //in setTotalMotion, the translation is set immediately afterwards.
    //Because of the dangers of the user not properly utilizing rawSetRobotAngle, it is private
    //Although the extra call to reset the translation in setRotation adds a couple of instruction
    //The logic should render accurate numbers consistently.

    constexpr chassis::Velocity2D zeroTranslation{0_mps, 0_mps};
    constexpr RPM zeroRotation{0.0};
    //Reset the translation
    mecanumLogic.setTotalMotion(zeroTranslation, zeroRotation, 0.0_rad);

    //Set translation then rotation, then apply new robot angle
    mecanumLogic.setTranslation(translation);
    mecanumLogic.setRotation(rotation);

    //This is to test if the new robot angle actually properly converts the field translation
    mecanumLogic.setRobotAngle(robotAngle);

    mecanumCalc.setWheelSpeeds(mecanumLogic.getWheelSpeeds());
    outputTranslation = mecanumCalc.getTranslation();
    outputRotation = mecanumCalc.getRotation();

    EXPECT_NEAR(outputTranslation.x.to<double>(), expectedRobotTranslation.x.to<double>(), k_tolerance);
    EXPECT_NEAR(outputTranslation.y.to<double>(), expectedRobotTranslation.y.to<double>(), k_tolerance);
    EXPECT_NEAR(outputRotation.to<double>(), rotation.to<double>(), k_tolerance);
}

INSTANTIATE_TEST_SUITE_P(zeroTest, FieldMecanumParameterTest,
                         testing::Values(std::make_tuple(chassis::Velocity2D{0_mps, 0_mps}, 0_rpm, 0_rad, 1_m, 1_m, 1_m)));

INSTANTIATE_TEST_SUITE_P(yTranslationTest, FieldMecanumParameterTest,
                         testing::Values(std::make_tuple(chassis::Velocity2D{0_mps, 234.23_mps}, 0_rpm, 0_rad, 1_m, 1_m, 1_m),
                                         std::make_tuple(chassis::Velocity2D{0_mps, -234_mps}, 0_rpm, 0_rad, 1_m, 1_m, 1_m),
                                         std::make_tuple(chassis::Velocity2D{0_mps, 12_mps}, 0_rpm, 0_rad, 1_m, 2_m, 4_m),
                                         std::make_tuple(chassis::Velocity2D{0_mps, -235.45_mps}, 0_rpm, 0_rad, 2_m, 1_m, 5.5_m)));

INSTANTIATE_TEST_SUITE_P(xTranslationTest, FieldMecanumParameterTest,
                         testing::Values(std::make_tuple(chassis::Velocity2D{234.23_mps, 0.0_mps}, 0_rpm, 0_rad, 1_m, 1_m, 1_m),
                                         std::make_tuple(chassis::Velocity2D{12.23_mps, 0.0_mps}, 0_rpm, 0_rad, 1_m, 1_m, 1_m),
                                         std::make_tuple(chassis::Velocity2D{234_mps, 0.0_mps}, 0_rpm, 0_rad, 2_m, 1_m, 4_m),
                                         std::make_tuple(chassis::Velocity2D{123.2_mps, 0.0_mps}, 0_rpm, 0_rad, 1_m, 3_m, 5.5_m)));

INSTANTIATE_TEST_SUITE_P(rotationTest, FieldMecanumParameterTest,
                         testing::Values(std::make_tuple(chassis::Velocity2D{0.0_mps, 0.0_mps}, 4_rpm, 0_rad, 1_m, 1_m, 1_m),
                                         std::make_tuple(chassis::Velocity2D{0.0_mps, 0.0_mps}, -234_rpm, 0_rad, 1_m, 1_m, 1_m),
                                         std::make_tuple(chassis::Velocity2D{0.0_mps, 0.0_mps}, 1.23_rpm, 0_rad, 1_m, 1_m, 1_m),
                                         std::make_tuple(chassis::Velocity2D{0.0_mps, 0.0_mps}, 5_rpm, 0_rad, 0.842_m, 0.234_m, 0.123_m)));

INSTANTIATE_TEST_SUITE_P(fieldAngleTest, FieldMecanumParameterTest,
                         testing::Values(std::make_tuple(chassis::Velocity2D{1.0_mps, 0.0_mps}, 0.0_rpm, 90_deg, 1_m, 1_m, 1_m),
                                         std::make_tuple(chassis::Velocity2D{0.0_mps, 1.0_mps}, 0.0_rpm, -90_deg, 1_m, 1_m, 1_m),
                                         std::make_tuple(chassis::Velocity2D{-23.0_mps, -2340.0_mps}, 0.0_rpm, 4353_rad, 1_m, 1_m, 4_m),
                                         std::make_tuple(chassis::Velocity2D{34.0_mps, 0.0_mps}, 0.0_rpm, -270_deg, 1_m, 1_m, 1_m)));