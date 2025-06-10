#include "turret_subsystem.hpp"
namespace control
{
    namespace turret
    {
        TurretSubsystem::TurretSubsystem(Drivers& drivers, const Config& config)
        :   m_imu{drivers.bmi088},
            m_yawHomeOffset{config.yawHomeOffset},
            m_ammoBooster{drivers, config.ammoBoosterConfig},
            m_feeder{drivers, config.feederConfig},
            m_gimbal{drivers, config.gimbalConfig},
            Subsystem(&drivers)
        {
        }

        void TurretSubsystem::flywheelsOn()
        {
            m_ammoBooster.flywheelsOn();
        }

        void TurretSubsystem::flywheelsOff()
        {
            //Prevent the feeder from jamming balls into still flywheels
            autoFireOff();
            m_ammoBooster.flywheelsOff();
        }

        void TurretSubsystem::autoFireOn()
        {
            if(m_ammoBooster.getFlywheelStatus())
            {
                m_feeder.feedOn();
            }
        }

        void TurretSubsystem::autoFireOff()
        {
            m_feeder.feedOff();
        }

        void TurretSubsystem::setPitch(const Radians& pitch)
        {
            m_gimbal.setPitch(pitch);
        }

        void TurretSubsystem::setFieldYaw(const Radians& yaw)
        {
            //If the chassis field yaw is 90 degrees
            //and the desired turret field yaw is 45 degrees
            //the robotwise yaw must be -45 degrees
            setRobotwiseYaw(yaw - getChassisFieldRotation());
        }

        Radians TurretSubsystem::getFieldYaw() const
        {
            return getRobotwiseYaw() + getChassisFieldRotation();
        }

        void TurretSubsystem::addFieldYaw(const Radians& angle)
        {
            setFieldYaw(getFieldYaw() + angle);
        }

        void TurretSubsystem::setRobotwiseYaw(const Radians& yaw)
        {
            //The desired robotwise yaw is 90 degrees
            //The difference between the yaw motor zero position
            //and the robot forward position is 45
            //The motor most be told to have a position of 45
            m_gimbal.setYaw(yaw - m_yawHomeOffset);
        }

        Radians TurretSubsystem::getRobotwiseYaw() const
        {
            //If the motor's yaw is 30 degrees
            //And the offset to the forward direction is 40 degree
            //The motor is 70 degrees relative to the forward direction
            return m_gimbal.getYaw()  + m_yawHomeOffset;
        }

        Radians TurretSubsystem::getChassisFieldRotation() const
        {
            return Radians{m_imu.getYaw()};
        }

        void TurretSubsystem::initialize()
        {
        }

        void TurretSubsystem::refresh()
        {
            m_ammoBooster.update();
            m_feeder.update();
            m_gimbal.update();
        }
    }
}