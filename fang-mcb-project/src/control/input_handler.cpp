#include "input_handler.hpp"
namespace control
{
    InputHandler::InputHandler(tap::communication::serial::Remote& remote, const config::motion::MotionConfig& motionConfig):
        m_remote{remote}, m_chassisInputHandler{remote, motionConfig} 
    {
    }

    control::chassis::ChassisInputHandler& InputHandler::getChassisInputs()
    {
        return m_chassisInputHandler;
    }
}