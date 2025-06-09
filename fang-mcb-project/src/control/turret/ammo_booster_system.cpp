#include "ammo_booster_system.hpp"
#include "drivers.hpp"

namespace control::turret
{
    AmmoBoosterSystem::AmmoBoosterSystem(Drivers& drivers, const Config& config)
    :  m_ammoVelocity{config.ammoVelocity}, m_leftFlywheel{drivers, config.leftFlywheelConfig}, m_rightFlywheel{drivers, config.rightFlywheelConfig}
    {
        setAmmoVelocity(config.ammoVelocity);
    }

    void AmmoBoosterSystem::flywheelsOn()
    {
        m_flywheelStatus = true;
        setRimSpeeds(m_ammoVelocity);
    }

    void AmmoBoosterSystem::flywheelsOff()
    {
        m_flywheelStatus = false;
        setRimSpeeds(k_stillSpeed);
    }

    bool AmmoBoosterSystem::getFlywheelStatus() const
    {
        return m_flywheelStatus;
    }

    void AmmoBoosterSystem::setAmmoVelocity(const MetersPerSecond& velocity)
    {
        m_ammoVelocity = velocity;
    }

    void AmmoBoosterSystem::setRimSpeeds(const MetersPerSecond& speed)
    {
        m_leftFlywheel.setTargetRimSpeed(speed);
        m_rightFlywheel.setTargetRimSpeed(speed);
        
    }

    void AmmoBoosterSystem::update()
    {
        m_leftFlywheel.update();
        m_rightFlywheel.update();
    }
}