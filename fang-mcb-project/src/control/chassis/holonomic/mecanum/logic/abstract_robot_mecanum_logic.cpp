#include "abstract_robot_mecanum_logic.hpp"

namespace chassis
{
    void AbstractRobotMecanumLogic::setMotion(const Translation2D& translation, double rotationalOffset)
    {
        setTranslation(translation);
        setRotationOffset(rotationalOffset);
    }

    void AbstractRobotMecanumLogic::setTranslation(const Translation2D& translation)
    {
        translation_ = translation;
    }

    void AbstractRobotMecanumLogic::setRotationOffset(double rotationalOffset)
    {
        rotationOffset_ = rotationalOffset;
    }

    Translation2D AbstractRobotMecanumLogic::getTranslation() const
    {
        return translation_;
    }

    double AbstractRobotMecanumLogic::getRotationOffset() const
    {
        return rotationOffset_;
    }

    AbstractQuadDriveData AbstractRobotMecanumLogic::getWheelSpeeds() const
    {
        return AbstractQuadDriveData{getFrontLeftWheelSpeed(), getFrontRightWheelSpeed(),
                             getRearLeftWheelSpeed(),  getRearRightWheelSpeed()};
    }

    double AbstractRobotMecanumLogic::getFrontLeftWheelSpeed() const
    {
        return translation_.y + translation_.x - rotationOffset_;
    }

    double AbstractRobotMecanumLogic::getFrontRightWheelSpeed() const
    {
        return translation_.y - translation_.x + rotationOffset_;
    }

    double AbstractRobotMecanumLogic::getRearLeftWheelSpeed() const
    {
        return translation_.y - translation_.x - rotationOffset_;
    }

    double AbstractRobotMecanumLogic::getRearRightWheelSpeed() const
    {
        return translation_.y + translation_.x + rotationOffset_;
    }
}