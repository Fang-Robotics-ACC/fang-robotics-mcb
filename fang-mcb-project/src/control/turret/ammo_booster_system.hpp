#ifndef FANG_ROBOTICS_MCB_CONTROL_AMMO_BOOSTER_HPP
#define FANG_ROBOTICS_MCB_CONTROL_AMMO_BOOSTER_HPP
#include "unitaliases.hpp"
#include "flywheel_system.hpp"
#include "drivers.hpp"

namespace control::turret
{
    /**
     * Manages two flywheels. Update must been called periodically.
     */
    class AmmoBoosterSystem
    {
    public:
    struct Config
    {
        MetersPerSecond ammoVelocity; 
        FlywheelSystem::Config leftFlywheelConfig;
        FlywheelSystem::Config rightFlywheelConfig;
    };
        AmmoBoosterSystem(Drivers& drivers, const Config& config);
        void autoFireOn();
        void autoFireOff();

        void setAmmoVelocity(const MetersPerSecond& velocity);
        void update();
    private:
        void setRimSpeeds(const MetersPerSecond& velocity);
        MetersPerSecond m_ammoVelocity;
        FlywheelSystem m_leftFlywheel;
        FlywheelSystem m_rightFlywheel;

    };
}
#endif