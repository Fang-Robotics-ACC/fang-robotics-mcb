#include "control/turret/turret_input_handler.hpp"

#include "tap/algorithms/math_user_utils.hpp"

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
            //return tap::algorithms::limitVal<double>(getRemotePitch() + getMousePitch(), mk_abstractMin, mk_abstractMax);
            return m_remote.getMouseY();
        }

        double TurretInputHandler::getYaw() const
        {
            //return tap::algorithms::limitVal<double>(getRemoteYaw() + getMouseYaw(), mk_abstractMin, mk_abstractMax);
            return m_remote.getMouseX();
        }

        double TurretInputHandler::getRemotePitch() const
        {

            return m_remote.getChannel(mk_remoteConfig.pitchChannel);

        }

        //Counterclockwise is positive
        double TurretInputHandler::getRemoteYaw() const
        {
            return -m_remote.getChannel(mk_remoteConfig.yawChannel);
        }

        double TurretInputHandler::getMousePitch() const
        {
            return m_remote.getMouseY() * mk_mouseConfig.pitchPercentagePerPx;
        }

        double TurretInputHandler::getMouseYaw() const
        {
            //Counterclockwise is positive
            return -m_remote.getMouseX() * mk_mouseConfig.yawPercentagePerPx;
        }

        bool TurretInputHandler::getFire() const
        {
            const double wheelValue{m_remote.getChannel(Remote::Channel::WHEEL)};
            return wheelValue >= mk_firingWheelThreshold;
        }
    }
}