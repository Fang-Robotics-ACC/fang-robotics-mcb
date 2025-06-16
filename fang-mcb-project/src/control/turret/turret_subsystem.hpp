#ifndef FANG_ROBOTICS_MCB_TURRET_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_TURRET_SUBSYSTEM_HPP
#include "control/turret/ammo_booster_system.hpp"
#include "control/turret/gimbal_system.hpp"
#include "control/turret/feeder_system.hpp"

#include "drivers.hpp"
#include "unitaliases.hpp"

#include "trap/communication/sensors/imu.hpp"

#include "tap/control/subsystem.hpp"
namespace control
{
    namespace turret
    {
        class TurretSubsystem : public virtual tap::control::Subsystem
        {
        public:
            using Imu = trap::communication::sensors::Imu;

            struct Config
            {
                GimbalSystem::Config gimbalConfig;
                AmmoBoosterSystem::Config ammoConfig;
                FeederSystem::Config feederConfig;
            };

            virtual void initialize() override;
            virtual void refresh() override;

            TurretSubsystem(Drivers& drivers, Imu& imu, const Config& config);
            void setFieldYaw(const Radians& yaw);
            void addFieldYaw(const Radians& angle);

            Radians getTargetFieldYaw() const;

            void setPitch(const Radians& pitch);
            Radians getPitch() const;
            void addPitch(const Radians& pitch);

            Radians getMaxPitch() const;
            Radians getMinPitch() const;

            void boosterOn();
            void boosterOff();

            void autoFireOn();
            void autoFireOff();

        private:
            void syncFieldYaw();
            Radians getChassisYaw() const;
            GimbalSystem m_gimbal;
            AmmoBoosterSystem m_booster;
            FeederSystem m_feeder;

            Imu& m_chassisImu;

            Radians m_targetFieldYaw{};
        };
    }
}
#endif
