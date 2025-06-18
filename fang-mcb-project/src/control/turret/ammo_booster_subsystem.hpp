#ifndef FANG_ROBOTICS_MCB_AMMO_BOOSTER_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_AMMO_BOOSTER_SUBSYSTEM_HPP
#include "drivers.hpp"
#include "control/turret/systems/ammo_booster_system.hpp"
#include "tap/control/subsystem.hpp"

namespace control::turret
    {
        class AmmoBoosterSubsystem: public virtual tap::control::Subsystem
        {
        public:
            using Config = AmmoBoosterSystem::Config;

            AmmoBoosterSubsystem(Drivers& drivers, const Config& config);

            void initialize() override;
            void refresh() override;

            void autoFireOn();
            void autoFireOff();

        private:
            AmmoBoosterSystem m_booster;
        };
    }

#endif