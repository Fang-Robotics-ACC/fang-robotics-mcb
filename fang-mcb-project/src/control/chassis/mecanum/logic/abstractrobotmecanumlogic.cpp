#include "abstractrobotmecanumlogic.hpp"

namespace chassis
{
    void AbstractRobotMecanumLogic::setMotion(const Translation2D& translation, double rotationalOffset)
    {
        setTranslation(translation);
        setRotationOffset(rotationalOffset);
    }

    void AbstractRobotMecanumLogic::setTranslation(const Translation2D& translation)
    {
        m_translation = translation;
    }

    void AbstractRobotMecanumLogic::setRotationOffset(double rotationalOffset)
    {
        m_rotationOffset = rotationalOffset;
    }

    Translation2D AbstractRobotMecanumLogic::getTranslation() const
    {
        return m_translation;
    }

    double AbstractRobotMecanumLogic::getRotationOffset() const
    {
        return m_rotationOffset;
    }

    AbstractQuadDriveData AbstractRobotMecanumLogic::getWheelSpeeds() const
    {
        return AbstractQuadDriveData{getFrontLeftWheelSpeed(), getFrontRightWheelSpeed(),
                             getRearLeftWheelSpeed(),  getRearRightWheelSpeed()};
    }

    double AbstractRobotMecanumLogic::getFrontLeftWheelSpeed() const
    {
        return m_translation.y + m_translation.x - m_rotationOffset;
    }

    double AbstractRobotMecanumLogic::getFrontRightWheelSpeed() const
    {
        return m_translation.y - m_translation.x + m_rotationOffset;
    }

    double AbstractRobotMecanumLogic::getRearLeftWheelSpeed() const
    {
        return m_translation.y - m_translation.x - m_rotationOffset;
    }

    double AbstractRobotMecanumLogic::getRearRightWheelSpeed() const
    {
        return m_translation.y + m_translation.x + m_rotationOffset;
    }
}