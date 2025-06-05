#ifndef INPUT_HANDLER_LSDFKJLJLJKZKLJSLKDJFLKJSEFLJ
#define INPUT_HANDLER_LSDFKJLJLJKZKLJSLKDJFLKJSEFLJ
#include "configuration/unitaliases.hpp"
#include "configuration/chassislogicaliases.hpp"

#include "control/chassis/chassis_input_handler.hpp"

#include "tap/communication/serial/remote.hpp"

namespace control
{
    class InputHandler
    {
    public:
    InputHandler(tap::communication::serial::Remote& remote);

    control::chassis::ChassisInputHandler& getChassisInputs();

    private:
    tap::communication::serial::Remote& m_remote;
    control::chassis::ChassisInputHandler m_chassisInputHandler;
    };
}
#endif