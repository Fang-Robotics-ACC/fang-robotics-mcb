#include "control/turret/turret_input_handler.hpp"

namespace control
{
    namespace turret
    {
        TurretInputHandler::TurretInputHandler(Remote& remote)
        :   m_remote{remote}
        {
        }

        double TurretInputHandler::getPitch() const
        {
            return m_remote.getChannel(Remote::Channel::RIGHT_VERTICAL);
        }

        double TurretInputHandler::getYaw() const
        {
            return m_remote.getChannel(Remote::Channel::RIGHT_HORIZONTAL);
        }
    }
}