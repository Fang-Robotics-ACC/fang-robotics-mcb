#include "unitlessrobotmecanumlogic.h"

namespace logic
{
    namespace chassis
    {
        void UnitlessRobotMecanumLogic::setMotion(const Translation2D& translation, double rotation)
        {
            m_translation = translation;
            m_rotation = rotation;
        }
    }
}