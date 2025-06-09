#ifndef FANG_ROBOTICS_MCB_TURRET_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_TURRET_SUBSYSTEM_HPP
#include "tap/control/subsystem.hpp"
#include "control/turret/ammo_booster_system.hpp"
#include "control/turret/feeder_system.hpp"
#include "control/turret/gimbal_system.hpp"

namespace control
{
    namespace turret
    {
        class TurretSubsystem : public tap::control::Subsystem
        {
        public:
            void flywheelsOn();
            void flywheelsOff();
            void autoFireOn();
            void autoFireOff();
            void setPitch();
            /**
             * This is relative to the field.
             */
            void setFieldYaw();

            void initialize() override;
            void refresh() override;
        };
    }
}
#endif