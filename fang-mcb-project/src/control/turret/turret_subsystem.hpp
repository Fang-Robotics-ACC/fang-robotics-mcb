#ifndef FANG_ROBOTICS_MCB_TURRET_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_TURRET_SUBSYSTEM_HPP
#include "control/turret/ammo_booster_system.hpp"
#include "control/turret/gimbal_system.hpp"
#include "control/turret/feeder_system.hpp"

#include "configuration/mathaliases.hpp"

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

            /**
             * yawHomeOffset - how many degrees the zero yaw of the yaw motor fr
             * the forward direction
             */
            struct Config
            {
                Degrees homeYawOffset;
                GimbalSystem::Config gimbalConfig;
                AmmoBoosterSystem::Config ammoConfig;
                FeederSystem::Config feederConfig;
            };

            virtual void initialize() override;
            virtual void refresh() override;

            TurretSubsystem(Drivers& drivers, Imu& imu, const Config& config);

            /**
             * Wherever the the yaw is aiming to look fieldwise, returns
             * a unit vector.
             */
            math::AbstractVector2D getTargetFieldDirection() const;

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
            static constexpr math::AbstractVector2D mk_forward{0.0, 1.0};
            void syncFieldYaw();
            Radians getChassisYaw() const;

            //Robotwise yaw where zero degrees is the forward direciton on the chassis
            void setRawTurretRobotwiseYaw(const Radians& yaw);
            const Radians mk_homeYawOffset;
            GimbalSystem m_gimbal;

            Imu& m_chassisImu;

            Radians m_targetFieldYaw{};
        };
    }
}
#endif
