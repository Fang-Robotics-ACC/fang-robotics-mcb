#include "chassis_input_handler.hpp"

#include "unitaliases.hpp"
#include "chassislogicaliases.hpp"

namespace control
{
    namespace chassis
    {

        ChassisInputHandler::ChassisInputHandler(Remote& remote, const MotionConfig& motionConfig)
            : m_remote{remote}, mk_motionConfig{motionConfig}
        {}
    }// namespce chassis
}// namespace control