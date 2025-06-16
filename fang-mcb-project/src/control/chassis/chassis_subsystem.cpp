#include "control/chassis/chassis_subsystem.hpp"
#include "unitaliases.hpp"

namespace control
{
    namespace chassis
    {
        ChassisSubsystem::ChassisSubsystem(Drivers& drivers, const ChassisConfig& chassisConfig)
            :
            tap::control::Subsystem::Subsystem{&drivers},
            m_drivers{drivers},
            mk_motorConfig{chassisConfig.chassisMotors},
            mk_dimensionConfig{chassisConfig.chassisDimensions},
            m_frontLeftMotor{drivers, mk_motorConfig.unifiedProperties, mk_motorConfig.frontLeftPwmData, mk_leftInversion},
            m_frontRightMotor{drivers, mk_motorConfig.unifiedProperties, mk_motorConfig.frontRightPwmData, mk_rightInversion},
            m_rearLeftMotor{drivers, mk_motorConfig.unifiedProperties, mk_motorConfig.rearLeftPwmData, mk_leftInversion},
            m_rearRightMotor{drivers, mk_motorConfig.unifiedProperties, mk_motorConfig.rearRightPwmdta, mk_rightInversion},
            m_mecanumLogic{mk_dimensionConfig.horizontalWheelDistance, mk_dimensionConfig.verticalWheelDistance, mk_dimensionConfig.wheelRadius},
            m_powerLimiter{drivers.refSerial, chassisConfig.powerLimiterConfig}

        {}

        void ChassisSubsystem::setMotion(const physics::Velocity2D& translation, const RPM& rotation)
        {
            m_mecanumLogic.setMotion(translation, rotation);
        }

        void ChassisSubsystem::setTranslation(const physics::Velocity2D& translation)
        {
            m_mecanumLogic.setTranslation(translation);
        }

        const physics::Velocity2D& ChassisSubsystem::getTranslation() const
        {
            return m_mecanumLogic.getTranslation();
        }

        void ChassisSubsystem::setRotation(const RPM& rotation)
        {
            m_mecanumLogic.setRotation(rotation);
        }

        RPM ChassisSubsystem::getRotation() const
        {
            return m_mecanumLogic.getRotation();
        }

        void ChassisSubsystem::initialize()
        {
            m_frontLeftMotor.initialize();
            m_frontRightMotor.initialize();
            m_rearLeftMotor.initialize();
            m_rearRightMotor.initialize();
        }

        void ChassisSubsystem::refresh()
        {
            syncWheelsToLogic();
            updateFieldAngle();
        }

        void ChassisSubsystem::syncWheelsToLogic()
        {
            m_frontLeftMotor.setSpeed(m_mecanumLogic.getFrontLeftWheelSpeed());
            m_frontRightMotor.setSpeed(m_mecanumLogic.getFrontRightWheelSpeed());
            m_rearLeftMotor.setSpeed(m_mecanumLogic.getRearLeftWheelSpeed());
            m_rearRightMotor.setSpeed(m_mecanumLogic.getRearRightWheelSpeed());
        }

        void ChassisSubsystem::updateFieldAngle()
        {
            const Radians currentFieldAngle{m_drivers.bmi088.getYaw()};
            m_mecanumLogic.setRobotAngle(currentFieldAngle);
        }
    }//namespace control
}//namespace chassis
