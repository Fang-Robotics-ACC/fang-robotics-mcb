#ifndef FANG_ROBOTICS_MCB_CHASSIS_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_CHASSIS_SUBSYSTEM_HPP
#include "drivers.hpp"
#include "unitaliases.hpp"
#include "data/directionality.hpp"
#include "physicsaliases.hpp"
#include "logic/chassis/fieldmecanumlogic.hpp"
#include "wrap/trap/communication/pwm_data.hpp"

#include "tap/communication/gpio/pwm.hpp"
#include "tap/control/subsystem.hpp"
#include "motors/gearboxrepeatultramk2.hpp"

namespace control
{
    namespace chassis
    {
        
        class ChassisSubsystem : public tap::control::Subsystem
        {
        public:
        using DriveMotor = motors::GearboxRepeatUltraMk2;

        struct ChassisMotorConfig
        {
            DriveMotor::UnifiedProperties unifiedProperties;
            trap::gpio::PwmData frontLeftPwmData;
            trap::gpio::PwmData frontRightPwmData;
            trap::gpio::PwmData rearLeftPwmData;
            trap::gpio::PwmData rearRightPwmdta;
        };

        struct ChassisDimensionConfig
        {
            Meters wheelRadius;
            Meters verticalWheelDistance;
            Meters horizontalWheelDistance;
        };

        struct ChassisConfig
        {
            ChassisDimensionConfig chassisDimensions;
            ChassisMotorConfig chassisMotors;
        };

        /**
         * The chassis config passes all of the relevant motor information.
         * This assumes that all pins are set to a single frequency.
         * This assumes all motors have the same gear ratio.
         */
        ChassisSubsystem(Drivers& drivers, const ChassisConfig& chassisConfig);

        /**
         * Simultaneously set the translation and rotation
         */
        void setMotion(const physics::Velocity2D& translation, const RPM& rotation);

        /**
         * This is relative to the field - the axis are basically wherever the robot
         * faces forward at the start of the round
         */
        void setTranslation(const physics::Velocity2D& translation);

        /**
         * This is relative to the field - the axis are basically wherever the robot
         * faces forward at the start of the round
         */
        const physics::Velocity2D& getTranslation() const;

        /**
         * Set the angular velocity of the chassis. Counterclockwise is positive.
         * This is due to ensuring consistency within mathematical convention. 
         * If you are taking the horizontal joystick position, you will likely need to
         * multiply it by -1.
         */
        void setRotation(const RPM& rotation);

        /**
         * Returns the angular velocity. Counterclockwise is positive in order to
         * match mathematical convention.
         */
        RPM getRotation() const;

        private:
            const data::motors::Directionality mk_defaultDirectionality{data::motors::Directionality::BIDIRECTIONAL};
            DriveMotor m_frontLeftMotor;
            DriveMotor m_frontRightMotor;
            DriveMotor m_rearLeftMotor;
            DriveMotor m_rearRightMotor;

            logic::chassis::FieldMecanumLogic m_mecanumLogic;

            const ChassisMotorConfig mk_motorConfig;
            const ChassisDimensionConfig mk_dimensionConfig; 

            ///If you are facing forward, and the platform moves forward,
            ///Then the left wheels will rotate counterclockwise, (when you are looking at the shaft)
            static const bool mk_leftInversion{false};

            ///If you are facing forward, and the platform moves forward,
            ///Then the right wheels will rotate clockwise, (when you are looking at the shaft)
            static const bool mk_rightInversion{true};
        };
    }//namespace chassis
}//namespace control
#endif