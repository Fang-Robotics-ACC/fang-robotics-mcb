#ifndef FANG_ROBOTICS_MCB_AMMO_BOOSTER_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_AMMO_BOOSTER_SUBSYSTEM_HPP
#include "driver/drivers.hpp"
#include "control/turret/system/ammo_booster_system.hpp"
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

            void refreshSafeDisconnect() override;


            void autoFireOn();
            void autoFireOff();

        private:
            AmmoBoosterSystem m_booster;
        };
    }

#endif