#include "wrap/units/units_alias.hpp"
#include "control/chassis/holonomic/mecanum/logic/abstract_field_mecanum_logic.hpp"
#include "control/chassis/holonomic/mecanum/logic/abstract_mecanum_calculator.hpp"

#include <gtest/gtest.h>

TEST(translationSetterGetterTest, AbstractFieldMecanumLogic)
{
    //The field translation should be consistent even though
    //AbstractFieldMecanumLogic rotates it relative to the robot
    //It is supposed to translate the offset consistently
    chassis::AbstractFieldMecanumLogic fieldMecanumLogic{};
    
    //Relative to field
    const Degrees facingLeft{90.0};
    //Lovely degree to radian conversion
    fieldMecanumLogic.setRobotAngle(facingLeft);

    const chassis::AbstractVelocity2D forward{0.0, 1.0};

    fieldMecanumLogic.setTranslation(forward);

    chassis::AbstractVelocity2D result{fieldMecanumLogic.getTranslation()};

    EXPECT_DOUBLE_EQ(result.x, forward.x);
    EXPECT_DOUBLE_EQ(result.y, forward.y);

    //Test integrity of translation when changing the angle
    const Degrees facingRight{-90.0};
    fieldMecanumLogic.setRobotAngle(facingRight);

    result = fieldMecanumLogic.getTranslation();
    EXPECT_DOUBLE_EQ(result.x, forward.x);
    EXPECT_DOUBLE_EQ(result.y, forward.y);

    const chassis::AbstractVelocity2D right{1.0, 0.0};
    fieldMecanumLogic.setTranslation(right);

    result = fieldMecanumLogic.getTranslation();
    EXPECT_DOUBLE_EQ(result.x, right.x);
    EXPECT_DOUBLE_EQ(result.y, right.y);
}

TEST(harderTranslationSetterGetterTest, AbstractFieldMecanumLogic)
{
    //The field translation should be consistent even though
    //AbstractFieldMecanumLogic rotates it relative to the robot
    //It is supposed to translate the offset consistently
    chassis::AbstractFieldMecanumLogic fieldMecanumLogic{};
    
    //Relative to field
    Degrees angle{43.2342};
    //Lovely degree to radian conversion
    fieldMecanumLogic.setRobotAngle(angle);

    chassis::AbstractVelocity2D movement{0.0, 0.0};

    fieldMecanumLogic.setTranslation(movement);

    chassis::AbstractVelocity2D result{fieldMecanumLogic.getTranslation()};

    EXPECT_DOUBLE_EQ(result.x, movement.x);
    EXPECT_DOUBLE_EQ(result.y, movement.y);

    angle = Degrees{0.0};
    fieldMecanumLogic.setRobotAngle(angle);

    result = fieldMecanumLogic.getTranslation();
    EXPECT_DOUBLE_EQ(result.x, movement.x);
    EXPECT_DOUBLE_EQ(result.y, movement.y);


    angle = Degrees{0.05};
    movement = chassis::AbstractVelocity2D{-23, -34};
    fieldMecanumLogic.setRobotAngle(angle);
    fieldMecanumLogic.setTranslation(movement);

    result = fieldMecanumLogic.getTranslation();
    EXPECT_DOUBLE_EQ(result.x, movement.x);
    EXPECT_DOUBLE_EQ(result.y, movement.y);

    angle = Degrees{-270};
    movement = chassis::AbstractVelocity2D{34.034, -34};
    fieldMecanumLogic.setRobotAngle(angle);
    fieldMecanumLogic.setTranslation(movement);

    result = fieldMecanumLogic.getTranslation();
    EXPECT_DOUBLE_EQ(result.x, movement.x);
    EXPECT_DOUBLE_EQ(result.y, movement.y);

    angle = Degrees{7056};
    movement = chassis::AbstractVelocity2D{-23, -34};
    fieldMecanumLogic.setRobotAngle(angle);
    fieldMecanumLogic.setTranslation(movement);

    result = fieldMecanumLogic.getTranslation();
    EXPECT_DOUBLE_EQ(result.x, movement.x);
    EXPECT_DOUBLE_EQ(result.y, movement.y);
}

TEST(AbstractFieldMecanumLogic, ZeroIsZero)
{
    //0 case
    chassis::AbstractMecanumCalculator calc{};
    chassis::AbstractFieldMecanumLogic fieldLogic{};
    chassis::AbstractVelocity2D expectedTranslation{0.0, -2.23};
    double expectedRotationOffset{20.0};

    fieldLogic.setMotion(expectedTranslation, expectedRotationOffset);
    fieldLogic.setRobotAngle(Degrees{0});

    calc.setWheelSpeeds(fieldLogic.getWheelSpeeds());


    EXPECT_DOUBLE_EQ(calc.getTranslation().x, expectedTranslation.x);
    EXPECT_DOUBLE_EQ(calc.getTranslation().y, expectedTranslation.y);
    EXPECT_DOUBLE_EQ(calc.getRotationOffset(), expectedRotationOffset);
}

TEST(AbstractFieldMecanumLogic, ForwardCase)
{
    chassis::AbstractMecanumCalculator calc{};
    chassis::AbstractFieldMecanumLogic fieldLogic{};
    chassis::AbstractVelocity2D expectedTranslation{0, 12.3};
    double expectedRotationOffset{0.0};

    fieldLogic.setMotion(expectedTranslation, expectedRotationOffset);
    fieldLogic.setRobotAngle(Degrees{0});

    calc.setWheelSpeeds(fieldLogic.getWheelSpeeds());

    EXPECT_DOUBLE_EQ(calc.getTranslation().x, expectedTranslation.x);
    EXPECT_DOUBLE_EQ(calc.getTranslation().y, expectedTranslation.y);
    EXPECT_DOUBLE_EQ(calc.getRotationOffset(), expectedRotationOffset);
}

TEST(AbstractFieldMecanumLogic, offsetAnglePositive)
{
    chassis::AbstractMecanumCalculator calc{};
    chassis::AbstractFieldMecanumLogic fieldLogic{};
    chassis::AbstractVelocity2D fieldTranslation{0, 1.0};
    double expectedRotationOffset{10.0};
    const Degrees robotAngle{90};

    fieldLogic.setMotion(fieldTranslation, expectedRotationOffset);
    fieldLogic.setRobotAngle(robotAngle);

    chassis::AbstractVelocity2D expectedTranslation{1.0, 0};

    calc.setWheelSpeeds(fieldLogic.getWheelSpeeds());

    EXPECT_DOUBLE_EQ(calc.getTranslation().x, expectedTranslation.x);
    EXPECT_DOUBLE_EQ(calc.getTranslation().y, expectedTranslation.y);
    EXPECT_DOUBLE_EQ(calc.getRotationOffset(), expectedRotationOffset);
}



