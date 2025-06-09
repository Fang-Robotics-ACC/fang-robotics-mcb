#ifndef FANG_ROBOTICS_MCB_TURRET_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_TURRET_SUBSYSTEM_HPP
#include "control/turret/ammo_booster_system.hpp"
#include "control/turret/feeder_system.hpp"
#include "control/turret/gimbal_system.hpp"

#include "tap/control/subsystem.hpp"
#include "tap/communication/sensors/imu/bmi088/bmi088.hpp"

#include "drivers.hpp"

namespace control
{
    namespace turret
    {
        class TurretSubsystem : public tap::control::Subsystem
        {
        public:
            struct Config
            {
                AmmoBoosterSystem::Config ammoBoosterConfig;
                FeederSystem::Config feederConfig;
                GimbalSystem::Config gimbalConfig;
            };
            TurretSubsystem(Drivers& drivers, const Config& config);
            void flywheelsOn();
            void flywheelsOff();
            /**
             * This will only be activated if the flywheels are on
             */
            void autoFireOn();
            void autoFireOff();
            void setPitch(const Radians& pitch);
            /**
             * This is relative to the field.
             */
            void setFieldYaw(const Radians& yaw);

            void initialize() override;
            void refresh() override;
        private:
            tap::communication::sensors::imu::bmi088::Bmi088& m_imu;
            AmmoBoosterSystem m_ammoBooster;
            FeederSystem m_feeder;
            GimbalSystem m_gimbal;
        };
    }
}
#endif