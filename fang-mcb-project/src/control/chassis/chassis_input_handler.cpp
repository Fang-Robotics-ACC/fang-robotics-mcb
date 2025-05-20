#include "chassis_input_handler.hpp"

#include "unitaliases.hpp"
#include "chassislogicaliases.hpp"

namespace control
{
    namespace chassis
    {

        ChassisInputHandler::ChassisInputHandler(Remote& remote) : m_remote{remote}
        {}
    }// namespce chassis
}// namespace control