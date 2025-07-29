#include "abstract_robot_mecanum_logic.hpp"

namespace fang::chassis
{
    void AbstractRobotMecanumLogic::setMotion(const AbstractVelocity2D& translation, double rotationalOffset)
    {
        setTranslation(translation);
        setRotationOffset(rotationalOffset);
    }

    void AbstractRobotMecanumLogic::setTranslation(const AbstractVelocity2D& translation)
    {
        translation_ = translation;
    }

    void AbstractRobotMecanumLogic::setRotationOffset(double rotationalOffset)
    {
        rotationOffset_ = rotationalOffset;
    }

    AbstractVelocity2D AbstractRobotMecanumLogic::getTranslation() const
    {
        return translation_;
    }

    double AbstractRobotMecanumLogic::getRotationOffset() const
    {
        return rotationOffset_;
    }

    AbstractQuadSpeeds AbstractRobotMecanumLogic::getWheelSpeeds() const
    {
        return
        {
            getFrontLeftWheelSpeed(), getFrontRightWheelSpeed(),
            getRearLeftWheelSpeed(),  getRearRightWheelSpeed()
        };
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