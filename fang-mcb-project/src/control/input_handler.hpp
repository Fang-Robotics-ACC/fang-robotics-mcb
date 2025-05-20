#ifndef INPUT_HANDLER_LSDFKJLJLJKZKLJSLKDJFLKJSEFLJ
#define iINPUT_HANDLER_LSDFKJLJLJKZKLJSLKDJFLKJSEFLJ
#include "configuration/unitaliases.hpp"
#include "configuration/chassislogicaliases.hpp"
#include "configuration/motion_control_config.hpp"

#include "control/chassis/chassis_input_handler.hpp"

#include "tap/communication/serial/remote.hpp"

namespace control
{
    class InputHandler
    {
    public:
    InputHandler(tap::communication::serial::Remote& remote, const config::motion::MotionConfig& motionConfig);

    private:
    tap::communication::serial::Remote& m_remote;
    control::chassis::ChassisInputHandler m_chassisInputHandler;
    };
}
#endif