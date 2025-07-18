#ifndef FANG_ROBOTICS_MCB_CHASSIS_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_CHASSIS_SUBSYSTEM_HPP
#include "drivers.hpp"
#include "motor/data/directionality.hpp"
#include "control/chassis/holonomic/mecanum/logic/field_mecanum_logic.hpp"
#include "util/physics/data/velocity_2d.hpp"
#include "wrap/units/units_alias.hpp"
#include "wrap/trap/communication/pwm_data.hpp"
#include "wrap/trap/control/chassis/power_limiter.hpp"

#include "wrap/trap/algorithms/ramp_2d.hpp"
#include "wrap/trap/algorithms/ramp.hpp"

#include "tap/communication/gpio/pwm.hpp"
#include "tap/control/subsystem.hpp"

#if defined(PLATFORM_HOSTED) && defined(ENV_UNIT_TESTS)
#include "test/mock/motor/gearboxrepeatultramk2mock.hpp"
#else
#include "motor/gearboxrepeatultramk2.hpp"
#endif

namespace control
{
    namespace chassis
    {
        
        class ChassisSubsystem : public tap::control::Subsystem
        {
        public:
#if defined(PLATFORM_HOSTED) && defined(ENV_UNIT_TESTS)
        using DriveMotor = mock::motor::GearboxRepeatUltraMk2Mock;
#else
        using DriveMotor = motor::GearboxRepeatUltraMk2;
#endif
        using PowerLimiter = trap::control::chassis::PowerLimiter;

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

        /**
         * Rotation Ramp Speed - how many RPM/s
         * Translation Ramp Speed - how how  many m/s/s
         */
        struct ChassisConfig
        {
            Hertz pwmFrequency;
            tap::gpio::Pwm::Timer pwmTimer;
            double translationRampSpeed;
            double rotationRampSpeed;
            ChassisDimensionConfig chassisDimensions;
            ChassisMotorConfig chassisMotors;
            PowerLimiter::Config powerLimiterConfig;
        };

        /**
         * The chassis config passes all of the relevant motor information.
         * This assumes that all pins are set to a single frequency.
         * This assumes all motor have the same gear ratio.
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

        void initialize() override;
        /**
         * Called regularly
         */
        void refresh() override;

        void refreshSafeDisconnect() override;

        private:
            void updateRamps();
            void syncLogicToRamps();
            void syncWheelsToLogic();
            void updateFieldAngle();
            void setPwmFrequency();
            Drivers& m_drivers;

            const Hertz mk_pwmFrequency;
            const tap::gpio::Pwm::Timer mk_pwmTimer;
            const double k_translationRampSpeed;
            const double k_rotationRampSpeed;
            const ChassisMotorConfig mk_motorConfig;
            const ChassisDimensionConfig mk_dimensionConfig; 

            const motor::Directionality mk_defaultDirectionality{motor::Directionality::BIDIRECTIONAL};
            DriveMotor m_frontLeftMotor;
            DriveMotor m_frontRightMotor;
            DriveMotor m_rearLeftMotor;
            DriveMotor m_rearRightMotor;

            ::chassis::FieldMecanumLogic m_mecanumLogic;

            PowerLimiter m_powerLimiter;
            ///If you are facing forward, and the platform moves forward,
            ///Then the left wheels will rotate counterclockwise, (when you are looking at the shaft)
            static const bool mk_leftInversion{false};

            ///If you are facing forward, and the platform moves forward,
            ///Then the right wheels will rotate clockwise, (when you are looking at the shaft)
            static const bool mk_rightInversion{true};

            trap::algorithms::Ramp2D<MetersPerSecond, Seconds> m_translationRamp{{0_mps,0_mps}, k_translationRampSpeed};
            trap::algorithms::Ramp<RPM, Seconds> m_rotationRamp{0_rpm, k_rotationRampSpeed};

        };
    }//namespace chassis
}//namespace control

#endif