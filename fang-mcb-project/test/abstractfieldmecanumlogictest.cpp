#include "abstractfieldmecanumlogic.hpp"
#include "chassislogicaliases.hpp"
#include "abstractmecanumcalculator.hpp"
#include "unitaliases.hpp"

#include "gtest/gtest.h"

TEST(translationSetterGetterTest, AbstractFieldMecanumLogic)
{
    //The field translation should be consistent even though
    //AbstractFieldMecanumLogic rotates it relative to the robot
    //It is supposed to translate the offset consistently
    logic::chassis::AbstractFieldMecanumLogic fieldMecanumLogic{};
    
    //Relative to field
    const Degrees facingLeft{90.0};
    //Lovely degree to radian conversion
    fieldMecanumLogic.setRobotAngle(facingLeft);

    const logic::chassis::Translation2D forward{0.0, 1.0};

    fieldMecanumLogic.setTranslation(forward);

    logic::chassis::Translation2D result{fieldMecanumLogic.getTranslation()};

    EXPECT_DOUBLE_EQ(result.x, forward.x);
    EXPECT_DOUBLE_EQ(result.y, forward.y);

    //Test integrity of translation when changing the angle
    const Degrees facingRight{-90.0};
    fieldMecanumLogic.setRobotAngle(facingRight);

    result = fieldMecanumLogic.getTranslation();
    EXPECT_DOUBLE_EQ(result.x, forward.x);
    EXPECT_DOUBLE_EQ(result.y, forward.y);

    const logic::chassis::Translation2D right{1.0, 0.0};
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
    logic::chassis::AbstractFieldMecanumLogic fieldMecanumLogic{};
    
    //Relative to field
    Degrees angle{43.2342};
    //Lovely degree to radian conversion
    fieldMecanumLogic.setRobotAngle(angle);

    logic::chassis::Translation2D movement{0.0, 0.0};

    fieldMecanumLogic.setTranslation(movement);

    logic::chassis::Translation2D result{fieldMecanumLogic.getTranslation()};

    EXPECT_DOUBLE_EQ(result.x, movement.x);
    EXPECT_DOUBLE_EQ(result.y, movement.y);

    angle = Degrees{0.0};
    fieldMecanumLogic.setRobotAngle(angle);

    result = fieldMecanumLogic.getTranslation();
    EXPECT_DOUBLE_EQ(result.x, movement.x);
    EXPECT_DOUBLE_EQ(result.y, movement.y);


    angle = Degrees{0.05};
    movement = logic::chassis::Translation2D{-23, -34};
    fieldMecanumLogic.setRobotAngle(angle);
    fieldMecanumLogic.setTranslation(movement);

    result = fieldMecanumLogic.getTranslation();
    EXPECT_DOUBLE_EQ(result.x, movement.x);
    EXPECT_DOUBLE_EQ(result.y, movement.y);

    angle = Degrees{-270};
    movement = logic::chassis::Translation2D{34.034, -34};
    fieldMecanumLogic.setRobotAngle(angle);
    fieldMecanumLogic.setTranslation(movement);

    result = fieldMecanumLogic.getTranslation();
    EXPECT_DOUBLE_EQ(result.x, movement.x);
    EXPECT_DOUBLE_EQ(result.y, movement.y);

    angle = Degrees{7056};
    movement = logic::chassis::Translation2D{-23, -34};
    fieldMecanumLogic.setRobotAngle(angle);
    fieldMecanumLogic.setTranslation(movement);

    result = fieldMecanumLogic.getTranslation();
    EXPECT_DOUBLE_EQ(result.x, movement.x);
    EXPECT_DOUBLE_EQ(result.y, movement.y);
}

TEST(AbstractFieldMecanumLogic, ZeroIsZero)
{
    //0 case
    logic::chassis::AbstractMecanumCalculator calc{};
    logic::chassis::AbstractFieldMecanumLogic fieldLogic{};
    logic::chassis::Translation2D expectedTranslation{0.0, -2.23};
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
    logic::chassis::AbstractMecanumCalculator calc{};
    logic::chassis::AbstractFieldMecanumLogic fieldLogic{};
    logic::chassis::Translation2D expectedTranslation{0, 12.3};
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
    logic::chassis::AbstractMecanumCalculator calc{};
    logic::chassis::AbstractFieldMecanumLogic fieldLogic{};
    logic::chassis::Translation2D fieldTranslation{0, 1.0};
    double expectedRotationOffset{10.0};
    const Degrees robotAngle{90};

    fieldLogic.setMotion(fieldTranslation, expectedRotationOffset);
    fieldLogic.setRobotAngle(robotAngle);

    logic::chassis::Translation2D expectedTranslation{1.0, 0};

    calc.setWheelSpeeds(fieldLogic.getWheelSpeeds());

    EXPECT_DOUBLE_EQ(calc.getTranslation().x, expectedTranslation.x);
    EXPECT_DOUBLE_EQ(calc.getTranslation().y, expectedTranslation.y);
    EXPECT_DOUBLE_EQ(calc.getRotationOffset(), expectedRotationOffset);
}



