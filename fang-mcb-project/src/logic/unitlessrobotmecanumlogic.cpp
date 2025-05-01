#include "unitlessrobotmecanumlogic.h"

namespace logic
{
    namespace chassis
    {
        void UnitlessRobotMecanumLogic::setMotion(const Translation2D& translation, double rotationalOffset)
        {
            m_translation = translation;
            m_rotationalOffset = rotationalOffset;
        }
    }
}