#include "control/turret/turret_input_handler.hpp"

namespace control
{
    namespace turret
    {
        TurretInputHandler::TurretInputHandler(Remote& remote, const Config& config)
        :   m_remote{remote},
            mk_remoteConfig{config.remoteConfig},
            mk_mouseConfig{config.mouseConfig}
        {

        }

        double TurretInputHandler::getPitch() const
        {
            return getRemotePitch();
        }

        double TurretInputHandler::getYaw() const
        {
            return getRemoteYaw();
        }

        double TurretInputHandler::getRemotePitch() const
        {

            return m_remote.getChannel(Remote::Channel::RIGHT_VERTICAL);

        }

        double TurretInputHandler::getRemoteYaw() const
        {
            return m_remote.getChannel(Remote::Channel::RIGHT_HORIZONTAL);
        }

        bool TurretInputHandler::getFire() const
        {
            const double wheelValue{m_remote.getChannel(Remote::Channel::WHEEL)};
            return wheelValue >= mk_firingWheelThreshold;
        }
    }
}