#include "gtest/gtest.h"
#include "fieldmecanumlogic.hpp"
#include "mecanumcalculator.hpp"
#include "chassislogicaliases.hpp"
#include "rotatevector2d.hpp"
#include "mathaliases.hpp"
#include <tuple>

//Expected velocity, expected angular velocity, robot angle
//Horizontal Distance, Vertical Distance, Wheel Radius
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
    mathAliases::AbstractVector2D strippedRobotTranslation{util::math::rotateVector2D(strippedTranslation, robotAngle)};
    logic::chassis::Velocity2D expectedTranslation{MetersPerSecond{strippedRobotTranslation.x}, MetersPerSecond{strippedRobotTranslation.y}};

    mecanumLogic.setTotalMotion(translation, rotation, robotAngle);
    mecanumCalc.setWheelSpeeds(mecanumLogic.getWheelSpeeds());
    const logic::chassis::Velocity2D outputTranslation{mecanumCalc.getTranslation()};
    const RPM outputRotation{mecanumCalc.getRotation()};

    EXPECT_DOUBLE_EQ(outputTranslation.x.to<double>(), expectedTranslation.x.to<double>());
    EXPECT_DOUBLE_EQ(outputTranslation.y.to<double>(), expectedTranslation.y.to<double>());
    EXPECT_DOUBLE_EQ(outputRotation.to<double>(), rotation.to<double>());
}