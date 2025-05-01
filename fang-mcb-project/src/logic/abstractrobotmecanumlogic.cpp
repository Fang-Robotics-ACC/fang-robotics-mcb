#include "abstractrobotmecanumlogic.hpp"

namespace logic
{
    namespace chassis
    {
        void AbstractRobotMecanumLogic::setMotion(const Translation2D& translation, double rotationalOffset)
        {
            m_translation = translation;
            m_rotationalOffset = rotationalOffset;
        }

        QuadDriveData AbstractRobotMecanumLogic::getWheelSpeeds() const
        {
            return QuadDriveData{getFrontLeftWheelSpeed(), getFrontRightWheelSpeed(),
                                 getRearLeftWheelSpeed(),  getRearRightWheelSpeed()};
        }

        double AbstractRobotMecanumLogic::getFrontLeftWheelSpeed() const
        {
            return m_translation.y + m_translation.x + m_rotationalOffset;
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
            return m_translation.y + m_translation.x - m_rotationalOffset;
        }
    }
}