#include "input_handler.hpp"
namespace control
{
    InputHandler::InputHandler(tap::communication::serial::Remote& remote):
        m_remote{remote}, m_chassisInputHandler{remote} 
    {
    }

    control::chassis::ChassisInputHandler& InputHandler::getChassisInputs()
    {
        return m_chassisInputHandler;
    }
}