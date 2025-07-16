#include "abstract_field_mecanum_logic.hpp"
#include "rotatevector2d.hpp"

#include <cmath>

namespace chassis
{
    void AbstractFieldMecanumLogic::setMotion(const Translation2D& translation, double rotationOffset)
    {
        setRotationOffset(rotationOffset);
        setTranslation(translation);
    }
    void AbstractFieldMecanumLogic::setTotalMotion(const Translation2D& translation, double rotationOffset, const Radians& robotAngle)
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
    void AbstractFieldMecanumLogic::setTranslation(const Translation2D& translation)
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
    Translation2D AbstractFieldMecanumLogic::getTranslation() const
    {
        return fieldTranslation_;
    }
    double AbstractFieldMecanumLogic::getRotationOffset() const
    {
        return robotwiseMecanumLogic_.getRotationOffset();
    }
    Translation2D AbstractFieldMecanumLogic::fieldToRobotTranslation(const Translation2D& translation) const
    {
        //If the robot is facing left and needs to move forward relative to the field,
        //Then the motion vector that is relative to the robot facing forwward needs to be rotated
        //in the opposite angle
        return util::math::rotateVector2D(translation, -robotAngle_);
    }
    Translation2D AbstractFieldMecanumLogic::robotToFieldTranslation(const Translation2D& translation) const
    {
        //If the robot is facing left and needs to move forward relative to the field,
        //Then the motion vector that is relative to the robot facing forwward needs to be rotated
        //in the opposite angle
        return util::math::rotateVector2D(translation, robotAngle_);
    }
    double AbstractFieldMecanumLogic::getFrontRightWheelSpeed() const
    {
        return robotwiseMecanumLogic_.getFrontRightWheelSpeed();
    }
    double AbstractFieldMecanumLogic::getFrontLeftWheelSpeed() const
    {
        return robotwiseMecanumLogic_.getFrontLeftWheelSpeed();
    }
    double AbstractFieldMecanumLogic::getRearLeftWheelSpeed() const
    {
        return robotwiseMecanumLogic_.getRearLeftWheelSpeed();
    }
    double AbstractFieldMecanumLogic::getRearRightWheelSpeed() const
    {
        return robotwiseMecanumLogic_.getRearRightWheelSpeed();
    }
    AbstractQuadDriveData AbstractFieldMecanumLogic::getWheelSpeeds() const
    {
        return robotwiseMecanumLogic_.getWheelSpeeds();
    }
}