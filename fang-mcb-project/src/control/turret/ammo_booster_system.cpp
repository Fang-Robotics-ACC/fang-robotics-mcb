#include "ammo_booster_system.hpp"
#include "drivers.hpp"

namespace control::turret
{
    AmmoBoosterSystem::AmmoBoosterSystem(Drivers& drivers, const Config& config)
    :  m_ammoVelocity{config.ammoVelocity}, m_leftFlywheel{drivers, config.leftFlywheelConfig}, m_rightFlywheel{drivers, config.rightFlywheelConfig}
    {
        setAmmoVelocity(config.ammoVelocity);
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

}