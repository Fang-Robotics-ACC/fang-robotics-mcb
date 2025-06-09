#include "turret_input_handler.hpp"

namespace control
{
    namespace turret
    {
        TurretInputHandler::TurretInputHandler(Remote& remote)
        :   m_remote{remote}
        {
        }

        void TurretInputHandler::setInputType(InputType inputType)
        {
            m_inputType = inputType;
        }

        
        double TurretInputHandler::getPitch() const
        {
            switch(m_inputType)
            {
                case InputType::REMOTE:
                return getRemotePitch();
                break;
            }
        }

        double TurretInputHandler::getYaw() const
        {
            switch(m_inputType)
            {
                case InputType::REMOTE:
                return getRemoteYaw();
                break;
            }
        }

        double TurretInputHandler::getRemotePitch() const
        {
            return m_remote.getChannel(Remote::Channel::LEFT_VERTICAL);
        }

        double TurretInputHandler::getRemoteYaw() const
        {
            //Left should be clounterclockwise, but that needs to be positive
            return -m_remote.getChannel(Remote::Channel::LEFT_HORIZONTAL);
        }

    }
}