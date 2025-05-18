#include "control/chassis/chassis_subsystem.hpp"

namespace control
{
    namespace chassis
    {
        ChassisSubsystem::ChassisSubsystem(Drivers& drivers, const ChassisConfig& chassisConfig)
            :
            mk_motorConfig{chassisConfig.chassisMotors},
            mk_dimensionConfig{chassisConfig.chassisDimensions},
            m_frontLeftMotor{mk_motorConfig.unifiedProperties, mk_motorConfig.frontLeftPwmData, mk_leftInversion},
            m_frontRightMotor{mk_motorConfig.unifiedProperties, mk_motorConfig.frontRightPwmData, mk_rightInversion},
            m_rearLeftMotor{mk_motorConfig.unifiedProperties, mk_motorConfig.rearLeftPwmData, mk_leftInversion},
            m_rearRightMotor{mk_motorConfig.unifiedProperties, mk_motorConfig.rearRightPwmdta, mk_rightInversion},
            m_mecanumLogic{mk_dimensionConfig.horizontalWheelDistance, mk_dimensionConfig.verticalWheelDistance, mk_dimensionConfig.wheelRadius}
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
    }//namespace control
}//namespace chassis
