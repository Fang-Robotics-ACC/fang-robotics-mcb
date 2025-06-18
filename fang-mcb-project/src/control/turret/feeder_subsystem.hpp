#ifndef FANG_ROBOTICS_MCB_FEEDER_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_FEEDER_SUBSYSTEM_HPP
#include "feeder_system.hpp"
#include "drivers.hpp"
#include "tap/control/subsystem.hpp"

namespace control::turret
    {
        class FeederSubsystem: public virtual tap::control::Subsystem
        {
        public:
            using Config = FeederSystem::Config;

            FeederSubsystem(Drivers& drivers, const Config& config);

            void initialize() override;
            void refresh() override;

            void autoFireOn();
            void autoFireOff();

        private:
            FeederSystem m_feeder;
        };
    }

#endif