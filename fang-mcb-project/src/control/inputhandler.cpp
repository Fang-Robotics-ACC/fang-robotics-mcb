#include "inputhandler.hpp"
namespace control
{
    InputHandler::InputHandler(tap::communication::serial::Remote& remote):
        m_remote{remote}
    {
    }
}