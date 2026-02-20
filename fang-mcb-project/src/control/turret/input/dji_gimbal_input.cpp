#include "control/turret/input/dji_gimbal_input.hpp"

#include "tap/algorithms/math_user_utils.hpp"

namespace fang::turret
{
    DjiGimbalInput::DjiGimbalInput(Remote& remote, const Config& config)
    :   m_remote{remote},
        mk_remoteConfig{config.remoteConfig},
        mk_mouseConfig{config.mouseConfig}
    {
    }

    double DjiGimbalInput::getPitch() const
    {
        return tap::algorithms::limitVal<double>(getRemotePitch() + getMousePitch(), mk_abstractMin, mk_abstractMax);
    }

    double DjiGimbalInput::getYaw() const
    {
        return tap::algorithms::limitVal<double>(getRemoteYaw() + getMouseYaw(), mk_abstractMin, mk_abstractMax);
    }

    double DjiGimbalInput::getRemotePitch() const
    {

        return m_remote.getChannel(mk_remoteConfig.pitchChannel);

    }

    //Counterclockwise is positive
    double DjiGimbalInput::getRemoteYaw() const
    {
        return -m_remote.getChannel(mk_remoteConfig.yawChannel);
    }

    double DjiGimbalInput::getMousePitch() const
    {
        //On mouse, down is positive due to VGA history ahhhh
        return -m_remote.getMouseY() * mk_mouseConfig.pitchPercentagePerPx;
    }

    double DjiGimbalInput::getMouseYaw() const
    {
        //Counterclockwise is positive
        return -m_remote.getMouseX() * mk_mouseConfig.yawPercentagePerPx;
    }

    bool DjiGimbalInput::getFire() const
    {
        const double wheelValue{m_remote.getChannel(Remote::Channel::WHEEL)};
        return wheelValue >= mk_firingWheelThreshold;
    }
}