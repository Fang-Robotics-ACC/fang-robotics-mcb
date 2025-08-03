#pragma once
#include "wrap/rail/turret/isimple_ammo_booster.hpp"
#include "tap/control/subsystem.hpp"
namespace fang::turret
{
    class SimpleAmmoBoosterSubsystem:
        virtual public ISimpleAmmoBooster,
        public tap::control::Subsystem
    {
    public:
        SimpleAmmoBoosterSubsystem(tap::Drivers& drivers) : Subsystem(&drivers)
        {}

        virtual ~SimpleAmmoBoosterSubsystem() = default;

        //Prevent ambiguity errors
        virtual void initialize() = 0;

    };
} 