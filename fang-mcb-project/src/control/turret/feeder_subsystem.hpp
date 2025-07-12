#ifndef FANG_ROBOTICS_MCB_FEEDER_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_FEEDER_SUBSYSTEM_HPP
#include "control/turret/system/feeder_system.hpp"
#include "drivers.hpp"
#include "control/turret/util/heat_limiter.hpp"
#include "tap/control/subsystem.hpp"

namespace control::turret
    {
        class FeederSubsystem: public virtual tap::control::Subsystem
        {
        public:
            using HeatLimiter = control::turret::HeatLimiter;
            using FeederSystem = control::turret::FeederSystem;
            struct Config
            {
                HeatLimiter::Config heatLimiterConfig;
                FeederSystem::Config feederConfig;
            };

            FeederSubsystem(Drivers& drivers, const Config& config);

            void initialize() override;
            void refresh() override;

            void refreshSafeDisconnect() override;

            void autoFireOn();
            void autoFireOff();

            void unjamOn();
            void unjamOff();

        private:
            FeederSystem m_feeder;
            HeatLimiter  m_heatLimiter;
        };
    }

#endif