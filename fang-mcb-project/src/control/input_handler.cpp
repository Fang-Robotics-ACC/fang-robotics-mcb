#include "input_handler.hpp"
namespace control
{
    InputHandler::InputHandler(tap::communication::serial::Remote& remote):
        m_remote{remote}
    {
    }

    
}