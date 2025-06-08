#ifndef FANG_ROBOTICS_MCB_GIMBAL_SYSTEM_HPP
#define FANG_ROBOTICS_MCB_GIMBAL_SYSTEM_HPP
#include "unitaliases.hpp"

#if defined(PLATFORM_HOSTED) && defined(ENV_UNIT_TESTS)
#include "test/mock/trap/motor/dji_gm6020_mock.hpp"
#else
#include "trap/motor/dji_gm6020.hpp"
#endif


namespace control
{
    namespace turret
    {
        class GimbalSystemClass
        {
        public:
        #if defined(PLATFORM_HOSTED) && defined(ENV_UNIT_TESTS)
        using PositionMotor = trap::mock::motor::DjiGM6020Mock;
        #else
        using PositionMotor = trap::motor::DjiGM6020;
        #endif
            
            /**
             * The pitch assumes 0 being the perfect horizontal angle relative to the ground
             * Negative is downward, positive is upwards. This is clamped to whatever
             * min pitch and max pitch is set to.
             */
            void setPitch(const Radians& pitch);

            /**
             * This adds a pitch amount to the current pitch
             */
            void addPitch(const Radians& pitchAmount);
            Radians getPitch() const;

            /**
             * Positive is counterclockwise from above.
             */
            void setYaw(const Radians yaw);
            /**
             * Adds an amount to the current yaw
             */
            void addYaw(const Radians yawAmount);
            Radians getYaw() const;
        private:
            PositionMotor m_pitchMotor;
            PositionMotor m_yawMotor;
            Radians m_minPitch;
            Radians m_maxPitch;
        };
    }
}
#endif