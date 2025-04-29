#ifndef INPUT_HANDLER_LSDFKJLJLJKZKLJSLKDJFLKJSEFLJ
#define iINPUT_HANDLER_LSDFKJLJLJKZKLJSLKDJFLKJSEFLJ
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