#include "abstractfieldmecanumlogic.hpp"
#include "chassislogicaliases.hpp"
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
