#ifndef FANG_ROBOTICS_MCB_GIMBAL_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_GIMBAL_SUBSYSTEM_HPP
#include "drivers.hpp"
#include "control/turret/system/gimbal_system.hpp"
#include "wrap/units/units_alias.hpp"

#include "trap/communication/sensors/imu.hpp"

#include "tap/control/subsystem.hpp"

namespace control
{
    namespace turret
    {
        class GimbalSubsystem : public virtual tap::control::Subsystem
        {
        public:

            using Imu = trap::communication::sensors::Imu;

            struct Config
            {
                Degrees homeYawOffset;
                GimbalSystem::Config gimbalConfig;
            };

            /**
             * yawHomeOffset - how many degrees the zero yaw of the yaw motor fr
             * the forward direction
             */

            virtual void initialize() override;
            virtual void refresh() override;

            GimbalSubsystem(Drivers& drivers, Imu& chassisImu, const Config& config);

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