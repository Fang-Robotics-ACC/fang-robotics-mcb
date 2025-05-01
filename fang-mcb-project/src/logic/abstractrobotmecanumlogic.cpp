#include "abstractrobotmecanumlogic.hpp"

namespace logic
{
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
            m_rotationalOffset = rotationalOffset;
        }

        Translation2D AbstractRobotMecanumLogic::getTranslation() const
        {
            return m_translation;
        }

        double AbstractRobotMecanumLogic::getRotationOffset() const
        {
            return m_rotationalOffset;
        }

        QuadDriveData AbstractRobotMecanumLogic::getWheelSpeeds() const
        {
            return QuadDriveData{getFrontLeftWheelSpeed(), getFrontRightWheelSpeed(),
                                 getRearLeftWheelSpeed(),  getRearRightWheelSpeed()};
        }

        double AbstractRobotMecanumLogic::getFrontLeftWheelSpeed() const
        {
            return m_translation.y + m_translation.x - m_rotationalOffset;
        }

        double AbstractRobotMecanumLogic::getFrontRightWheelSpeed() const
        {
            return m_translation.y - m_translation.x + m_rotationalOffset;
        }

        double AbstractRobotMecanumLogic::getRearLeftWheelSpeed() const
        {
            return m_translation.y - m_translation.x - m_rotationalOffset;
        }

        double AbstractRobotMecanumLogic::getRearRightWheelSpeed() const
        {
            return m_translation.y + m_translation.x + m_rotationalOffset;
        }
    }
}