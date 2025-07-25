#ifndef FANG_ROBOTICS_MCB_CONTROL_AMMO_BOOSTER_HPP
#define FANG_ROBOTICS_MCB_CONTROL_AMMO_BOOSTER_HPP
#include "flywheel_system.hpp"
#include "driver/drivers.hpp"

#include "wrap/units/units_alias.hpp"

namespace fang::turret
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
        OldFlywheelSystem::Config leftFlywheelConfig;
        OldFlywheelSystem::Config rightFlywheelConfig;
    };
        AmmoBoosterSystem(Drivers& drivers, const Config& config);
        void autoFireOn();
        void autoFireOff();

        void setAmmoVelocity(const MetersPerSecond& velocity);
        void update();
        void initialize();
    private:
        void setRimSpeeds(const MetersPerSecond& velocity);
        MetersPerSecond m_ammoVelocity;
        OldFlywheelSystem m_leftFlywheel;
        OldFlywheelSystem m_rightFlywheel;

        static constexpr MetersPerSecond k_stillSpeed{0};

    };
}
#endif