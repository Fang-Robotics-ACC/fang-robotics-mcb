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
            /**
             * yawHomeOffset - yawMotorZeroPosition minus forwardDirection
             * counterclockwise from above is positive. 
             */
            struct Config
            {
                Radians yawHomeOffset;
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
            /**
             * The difference between the home yaw motor 
             * and the robot forward angle must be taken into consideration
             */
            void setRobotwiseYaw(const Radians& angle) ;
            Radians getRobotwiseYaw();

            Radians getChassisFieldRotation() const;
            /**
             * Returns the turrets rotation relative to the robot. 0 should be forward.
             */

            tap::communication::sensors::imu::bmi088::Bmi088& m_imu;
            const Radians m_yawHomeOffset;
            AmmoBoosterSystem m_ammoBooster;
            FeederSystem m_feeder;
            GimbalSystem m_gimbal;
        };
    }
}
#endif