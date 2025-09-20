#include "proxy_turret_input.hpp"

namespace fang::turret
{
    ProxyTurretInput::ProxyTurretInput(const Config& config)
        :
        kConfig_{config}
    {
    }

    void ProxyTurretInput::setPitch(double pitch)
    {
        pitch_ = pitch * kConfig_.pitchScale;
    }

    double ProxyTurretInput::getPitch() const
    {
        return pitch_;
    }

    void ProxyTurretInput::setYaw(double yaw)
    {
        yaw_ = yaw * kConfig_.yawScale;
    }

    double ProxyTurretInput::getYaw() const
    {
        return yaw_;
    }
}