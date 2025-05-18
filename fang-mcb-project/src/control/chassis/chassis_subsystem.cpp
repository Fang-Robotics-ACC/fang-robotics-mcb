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
    }//namespace control
}//namespace chassis
