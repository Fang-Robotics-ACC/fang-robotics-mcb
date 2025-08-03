#pragma once

#include "driver/drivers.hpp"
#include "control/turret/ammo_booster/simple_ammo_booster_subsystem/simple_ammo_booster_subsystem.hpp"

#include "wrap/rail/motor/ispeed_wheel.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::turret
{
    /**
     * Manages two flywheels. Update must been called periodically.
     * Assumes they are horizontal.
     */
    class SimpleAmmoBooster : public SimpleAmmoBoosterSubsystem
    {
    public:
        using Flywheel = motor::ISpeedWheel;
        using Flywheels = std::vector<std::unique_ptr<Flywheel>>;
        struct Config
        {
            MetersPerSecond ammoVelocity; 
        };

        /**
         * You need to std::move the vector of flywheels.
         * Theoretically, it should throw an error should you attempt
         * to copy unique pointers.
         */
        SimpleAmmoBooster
        (
            Drivers& drivers,
            Flywheels&& flywheels,
            const Config& config
        );

        void boostOn() override;
        void boostOff() override;

        void update() override;
        void refresh() override;
        void initialize() override;
    private:
        static constexpr MetersPerSecond kStillSpeed{0};

        void setRimSpeeds(const MetersPerSecond& velocity);
        MetersPerSecond ammoVelocity_;
        Flywheels flywheels_;


    };
}