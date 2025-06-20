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
            mk_pwmFrequency{chassisConfig.pwmFrequency},
            mk_pwmTimer{chassisConfig.pwmTimer},
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
            setPwmFrequency();
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

        void ChassisSubsystem::refreshSafeDisconnect()
        {
            m_frontLeftMotor.setSpeed(0_rpm);
            m_frontRightMotor.setSpeed(0_rpm);
            m_rearLeftMotor.setSpeed(0_rpm);
            m_rearRightMotor.setSpeed(0_rpm);
        }

        void ChassisSubsystem::syncWheelsToLogic()
        {
            //If we are exeeding power, we should downscale it for safety
            //Returns 0 if we are at or below the critical threshold
            //Reutnrs 1 if we are above the limiting threshold (buffer - crit)
            const float powerScale{m_powerLimiter.getPowerLimitRatio()};
            m_frontLeftMotor.setSpeed(m_mecanumLogic.getFrontLeftWheelSpeed() * powerScale);
            m_frontRightMotor.setSpeed(m_mecanumLogic.getFrontRightWheelSpeed() * powerScale);
            m_rearLeftMotor.setSpeed(m_mecanumLogic.getRearLeftWheelSpeed() * powerScale);
            m_rearRightMotor.setSpeed(m_mecanumLogic.getRearRightWheelSpeed() * powerScale);
        }

        void ChassisSubsystem::updateFieldAngle()
        {
            const Radians currentFieldAngle{m_drivers.bmi088.getYaw()};
            m_mecanumLogic.setRobotAngle(currentFieldAngle);
        }

        void ChassisSubsystem::setPwmFrequency()
        {
            m_drivers.pwm.setTimerFrequency(mk_pwmTimer, static_cast<double>(Hertz{mk_pwmFrequency}));
        }
    }//namespace control
}//namespace chassis
