#ifndef FANG_ROBOTICS_MCB_GIMBAL_SYSTEM_HPP
#define FANG_ROBOTICS_MCB_GIMBAL_SYSTEM_HPP
#include "unitaliases.hpp"
#include "drivers.hpp"

#if defined(PLATFORM_HOSTED) && defined(ENV_UNIT_TESTS)
#include "test/mock/trap/motor/dji_gm6020_mock.hpp"
#include "test/control/turret/gimbal_system_test.hpp"
#else
#include "trap/motor/dji_gm6020.hpp"
#endif

namespace control
{
    namespace turret
    {
        /**
         * This is designed to set a given pitch and yaw.
         * The yaw is relative to the motor mount.
         */
        class GimbalSystem
        {
        public:
            #if defined(PLATFORM_HOSTED) && defined(ENV_UNIT_TESTS)
            using PositionMotor = trap::mock::motor::DjiGM6020Mock;
                friend class test::GimbalSystemTest;
            #else
            using PositionMotor = trap::motor::DjiGM6020;
            #endif
            /**
             * minPitch - the lowest that the pitch motor will turn
             * maxPitch - the highest that the pitch motor will turn
             */
            struct Config
            {
                Degrees minPitch;
                Degrees maxPitch;
                PositionMotor::Config pitchMotorConfig;
                PositionMotor::Config yawMotorConfig;
            };

            GimbalSystem(Drivers& drivers, const Config& config);
            
            /**
             * The pitch assumes 0 being the perfect horizontal angle relative to mount.
             * Negative is downward, positive is upwards. This is clamped to whatever
             * min pitch and max pitch is set to.
             */
            void setPitch(const Radians& pitch);

            /**
             * This adds a pitch amount to the current pitch
             */
            void addPitch(const Radians& angle);
            Radians getPitch() const;
            Radians getMaxPitch() const;
            Radians getMinPitch() const;

            /**
             * Positive is counterclockwise from above.
             */
            void setYaw(const Radians& yaw);
            /**
             * Adds an amount to the current yaw
             */
            void addYaw(const Radians& angle);
            Radians getYaw() const;

            /**
             * Must be periodically called to keep motor pids
             * updated.
             */
            void update();

            void initialize();
        private:
            Radians m_minPitch;
            Radians m_maxPitch;
            PositionMotor m_pitchMotor;
            PositionMotor m_yawMotor;
        };
    }
}
#endif