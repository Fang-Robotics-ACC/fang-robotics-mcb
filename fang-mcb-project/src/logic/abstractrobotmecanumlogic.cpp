#include "abstractrobotmecanumlogic.h"

namespace logic
{
    namespace chassis
    {
        void AbstractRobotMecanumLogic::setMotion(const Translation2D& translation, double rotationalOffset)
        {
            m_translation = translation;
            m_rotationalOffset = rotationalOffset;
        }
    }
}