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

    }
}