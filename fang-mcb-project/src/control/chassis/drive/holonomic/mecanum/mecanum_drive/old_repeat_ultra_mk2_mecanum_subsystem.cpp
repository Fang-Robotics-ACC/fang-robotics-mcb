#include "old_repeat_ultra_mk2_mecanum_subsystem.hpp"

#include "wrap/units/units_alias.hpp"


namespace fang::chassis
{
    RepeatUltraMk2MecanumSubsystem::RepeatUltraMk2MecanumSubsystem(Drivers& drivers, const ChassisConfig& chassisConfig):
        HolonomicSubsystem{drivers},
        m_drivers{drivers},
        mk_pwmFrequency{chassisConfig.pwmFrequency},
        mk_pwmTimer{chassisConfig.pwmTimer},
        k_translationRampSpeed{chassisConfig.translationRampSpeed},
        k_rotationRampSpeed{chassisConfig.rotationRampSpeed},
        mk_motorConfig{chassisConfig.chassisMotors},
        mk_dimensionConfig{chassisConfig.chassisDimensions},
        m_frontLeftMotor{drivers, mk_motorConfig.unifiedProperties, mk_motorConfig.frontLeftPwmData, mk_leftInversion},
        m_frontRightMotor{drivers, mk_motorConfig.unifiedProperties, mk_motorConfig.frontRightPwmData, mk_rightInversion},
        m_rearLeftMotor{drivers, mk_motorConfig.unifiedProperties, mk_motorConfig.rearLeftPwmData, mk_leftInversion},
        m_rearRightMotor{drivers, mk_motorConfig.unifiedProperties, mk_motorConfig.rearRightPwmdta, mk_rightInversion},
        m_mecanumLogic{mk_dimensionConfig.horizontalWheelDistance, mk_dimensionConfig.verticalWheelDistance, mk_dimensionConfig.wheelRadius},
        m_powerLimiter{drivers.refSerial, chassisConfig.powerLimiterConfig}

    {}

    void RepeatUltraMk2MecanumSubsystem::setMotion(const physics::Velocity2D& translation, const RPM& rotation)
    {
        setTargetTranslation(translation);
        setTargetRotation(rotation);
    }

    void RepeatUltraMk2MecanumSubsystem::setTargetTranslation(const physics::Velocity2D& translation)
    {
        m_translationRamp.setTarget(translation);
    }

    const physics::Velocity2D& RepeatUltraMk2MecanumSubsystem::getTranslation() const
    {
        return m_mecanumLogic.getTranslation();
    }

    void RepeatUltraMk2MecanumSubsystem::setTargetRotation(const RPM& rotation)
    {

        m_rotationRamp.setTarget(rotation);
        //m_mecanumLogic.setRotation(rotation);
    }

    RPM RepeatUltraMk2MecanumSubsystem::getRotation() const
    {
        return m_mecanumLogic.getRotation();
    }

    void RepeatUltraMk2MecanumSubsystem::initialize()
    {
        setPwmFrequency();
        m_frontLeftMotor.initialize();
        m_frontRightMotor.initialize();
        m_rearLeftMotor.initialize();
        m_rearRightMotor.initialize();
    }

    void RepeatUltraMk2MecanumSubsystem::update()
    {
        refresh();
    }

    void RepeatUltraMk2MecanumSubsystem::refresh()
    {
        updateRamps();
        syncLogicToRamps();
        syncWheelsToLogic();
        updateFieldAngle();
    }

    void RepeatUltraMk2MecanumSubsystem::refreshSafeDisconnect()
    {
        m_frontLeftMotor.setTargetSpeed(0_rpm);
        m_frontRightMotor.setTargetSpeed(0_rpm);
        m_rearLeftMotor.setTargetSpeed(0_rpm);
        m_rearRightMotor.setTargetSpeed(0_rpm);
    }

    void RepeatUltraMk2MecanumSubsystem::updateRamps()
    {
        m_translationRamp.update();
        m_rotationRamp.update();
    }

    void RepeatUltraMk2MecanumSubsystem::syncLogicToRamps()
    {
        m_mecanumLogic.setTranslation(m_translationRamp.getValue());
        m_mecanumLogic.setRotation(m_rotationRamp.getValue());
    }

    void RepeatUltraMk2MecanumSubsystem::syncWheelsToLogic()
    {
        //If we are exeeding power, we should downscale it for safety
        //Returns 0 if we are at or below the critical threshold
        //Reutnrs 1 if we are above the limiting threshold (buffer - crit)
        const float powerScale{m_powerLimiter.getPowerLimitRatio()};
        const QuadDriveData wheelSpeeds{m_mecanumLogic.getWheelSpeeds()};
        m_frontLeftMotor.setTargetSpeed(wheelSpeeds.frontLeft * powerScale);
        m_frontRightMotor.setTargetSpeed(wheelSpeeds.frontRight * powerScale);
        m_rearLeftMotor.setTargetSpeed(wheelSpeeds.rearLeft * powerScale);
        m_rearRightMotor.setTargetSpeed(wheelSpeeds.rearRight * powerScale);
    }

    void RepeatUltraMk2MecanumSubsystem::updateFieldAngle()
    {
        const Radians currentFieldAngle{m_drivers.bmi088.getYaw()};
        m_mecanumLogic.setRobotAngle(currentFieldAngle);
    }

    void RepeatUltraMk2MecanumSubsystem::setPwmFrequency()
    {
        m_drivers.pwm.setTimerFrequency(mk_pwmTimer, static_cast<double>(Hertz{mk_pwmFrequency}));
    }
}//namespace chassis
