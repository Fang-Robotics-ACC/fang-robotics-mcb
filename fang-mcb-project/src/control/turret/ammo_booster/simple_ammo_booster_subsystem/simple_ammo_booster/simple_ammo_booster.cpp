#include "simple_ammo_booster.hpp"
#include "driver/drivers.hpp"

namespace fang::turret
{
    SimpleAmmoBooster::SimpleAmmoBooster(Drivers& drivers, Flywheels&& flywheels, const Config& config):
        SimpleAmmoBoosterSubsystem(drivers),
        ammoVelocity_{config.ammoVelocity},
        flywheels_{std::move(flywheels)}

    {
    }

    void SimpleAmmoBooster::boostOn()
    {
        setRimSpeeds(ammoVelocity_);
    }

    void SimpleAmmoBooster::boostOff()
    {
        setRimSpeeds(kStillSpeed);
    }

    void SimpleAmmoBooster::setRimSpeeds(const MetersPerSecond& speed)
    {
        for(std::unique_ptr<Flywheel>& flywheel : flywheels_)
        {
            flywheel->setTargetRimSpeed(speed);
        }
        
    }

    void SimpleAmmoBooster::update()
    {
        for(std::unique_ptr<Flywheel>& flywheel : flywheels_)
        {
            flywheel->update();
        }
    }

    void SimpleAmmoBooster::refresh()
    {
        update();
    }

    void SimpleAmmoBooster::initialize()
    {
        for(std::unique_ptr<Flywheel>& flywheel : flywheels_)
        {
            flywheel->initialize();
        }
    }
}