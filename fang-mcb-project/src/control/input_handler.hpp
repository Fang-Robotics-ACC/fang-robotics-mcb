#ifndef INPUT_HANDLER_LSDFKJLJLJKZKLJSLKDJFLKJSEFLJ
#define INPUT_HANDLER_LSDFKJLJLJKZKLJSLKDJFLKJSEFLJ
#include "control/chassis/chassis_input_handler.hpp"
#include "control/turret/turret_input_handler.hpp"
#include "wrap/units/units_alias.hpp"

#include "tap/communication/serial/remote.hpp"

namespace control
{
    class InputHandler
    {
    public:
    InputHandler(tap::communication::serial::Remote& remote);


    private:
    tap::communication::serial::Remote& m_remote;
    };
}
#endif