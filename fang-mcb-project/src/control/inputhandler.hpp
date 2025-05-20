#ifndef INPUT_HANDLER_LSDFKJLJLJKZKLJSLKDJFLKJSEFLJ
#define iINPUT_HANDLER_LSDFKJLJLJKZKLJSLKDJFLKJSEFLJ
#include "configuration/unitaliases.hpp"
#include "configuration/chassislogicaliases.hpp"

#include "tap/communication/serial/remote.hpp"

namespace control
{
    class InputHandler
    {
    public:
    InputHandler(tap::communication::serial::Remote& remote);

    logic::chassis::Velocity2D getChassisFieldTranslation() const;
    RPM getChassisFieldRotation() const;

    private:
    tap::communication::serial::Remote& m_remote;
    };
}
#endif