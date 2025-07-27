#include "abstract_field_mecanum_logic.hpp"
#include "util/math/geometry/rotate_vector_2d.hpp"

#include <cmath>

namespace fang::chassis
{
    void AbstractFieldMecanumLogic::setMotion(const AbstractVelocity2D& translation, double rotationOffset)
    {
        setRotationOffset(rotationOffset);
        setTranslation(translation);
    }

    void AbstractFieldMecanumLogic::setTotalMotion(const AbstractVelocity2D& translation, double rotationOffset, const Radians& robotAngle)
    {
        setRobotAngle(robotAngle);
        setRotationOffset(rotationOffset);
        setTranslation(translation);
    }

    void AbstractFieldMecanumLogic::setRobotAngle(const Radians& robotAngle)
    {
        //This must be obtained beforehand or else the new angle will result
        //in bogus being returned (the old field translation is relative to the old angle
        //not the new one.)
        robotAngle_ = robotAngle;
        //Update robot-centric translation to new angle
        setTranslation(fieldTranslation_);
    }

    void AbstractFieldMecanumLogic::setTranslation(const AbstractVelocity2D& translation)
    {
        //Counteract the robot's angle relative to the field
        fieldTranslation_ = translation;
        robotwiseMecanumLogic_.setTranslation(fieldToRobotTranslation(translation));
    }

    void AbstractFieldMecanumLogic::setRotationOffset(double rotationOffset)
    {
        robotwiseMecanumLogic_.setRotationOffset(rotationOffset);
    }

    Radians AbstractFieldMecanumLogic::getRobotAngle() const
    {
        return robotAngle_;
    }

    AbstractVelocity2D AbstractFieldMecanumLogic::getTranslation() const
    {
        return fieldTranslation_;
    }

    double AbstractFieldMecanumLogic::getRotationOffset() const
    {
        return robotwiseMecanumLogic_.getRotationOffset();
    }

    AbstractVelocity2D AbstractFieldMecanumLogic::fieldToRobotTranslation(const AbstractVelocity2D& translation) const
    {
        //If the robot is facing left and needs to move forward relative to the field,
        //Then the motion vector that is relative to the robot facing forwward needs to be rotated
        //in the opposite angle
        return math::rotateVector2D(translation, -robotAngle_);
    }

    AbstractVelocity2D AbstractFieldMecanumLogic::robotToFieldTranslation(const AbstractVelocity2D& translation) const
    {
        //If the robot is facing left and needs to move forward relative to the field,
        //Then the motion vector that is relative to the robot facing forwward needs to be rotated
        //in the opposite angle
        return math::rotateVector2D(translation, robotAngle_);
    }

    AbstractQuadSpeeds AbstractFieldMecanumLogic::getWheelSpeeds() const
    {
        return robotwiseMecanumLogic_.getWheelSpeeds();
    }
}