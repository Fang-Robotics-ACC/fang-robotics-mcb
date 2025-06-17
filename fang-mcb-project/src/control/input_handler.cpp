#include "input_handler.hpp"
namespace control
{
    InputHandler::InputHandler(tap::communication::serial::Remote& remote):
        m_remote{remote}, m_turretInputHandler{remote}
    {
    }

    control::turret::TurretInputHandler& InputHandler::getTurretInputs()
    {
        return m_turretInputHandler;
    }
}