#ifndef FANG_ROBOTICS_MCB_FEEDER_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_FEEDER_SUBSYSTEM_HPP
#include "feeder_system.hpp"
#include "tap/control/subsystem.hpp"

namespace control::turret
    {
        class FeederSubsystem: public virtual tap::control::Subsystem
        {
        public:

            /**
             * yawHomeOffset - how many degrees the zero yaw of the yaw motor fr
             * the forward direction
             */
            using Config = FeederSystem::Config;

            virtual void initialize() override;
            virtual void refresh() override;

            FeederSubsystem(Drivers& drivers, const Config& config);

            /**
             * Wherever the the yaw is aiming to look fieldwise, returns
             * a unit vector.
             */
            void autoFireOn();
            void autoFireOff();

        private:
            FeederSystem m_feeder;
        };
    }

#endif