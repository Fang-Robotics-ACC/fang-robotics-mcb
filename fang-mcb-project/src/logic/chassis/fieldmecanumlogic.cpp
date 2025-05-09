#include "fieldmecanumlogic.hpp"

namespace logic
{
    namespace chassis
    {
        FieldMecanumLogic::FieldMecanumLogic(const Meters& horizontalWheelDistance,
                                             const Meters& verticalWheelDistance,
                                             const Meters& wheelRadius):
        m_robotMecanumLogic{horizontalWheelDistance, verticalWheelDistance, wheelRadius}
        {}
    }//namespace chassis
}//namespace logic