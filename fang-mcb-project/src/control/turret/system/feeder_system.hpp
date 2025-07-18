#ifndef FANG_ROBOTICS_MCB_FEEDER_SYSTEM_HPP
#define FANG_ROBOTICS_MCB_FEEDER_SYSTEM_HPP
#include "wrap/units/units_alias.hpp"

#include "tap/motor/dji_motor.hpp"

#if defined(PLATFORM_HOSTED) && defined(ENV_UNIT_TESTS)
#include "test/mock/trap/motor/dji_m2006_mock.hpp"
#include "test/control/turret/feeder_system_test.hpp"
#else
#include "trap/motor/dji_m2006.hpp"
#endif

#include "driver/drivers.hpp"

namespace control
{
    namespace turret
    {
        /**
         * This controls the Feeder Motor. update() must be periodically called
         * to update the motor's associated PID.
         * 
         * This assumes that there is one feeder motor.
         */
        class FeederSystem
        {
        public:
        #if defined(PLATFORM_HOSTED) && defined(ENV_UNIT_TESTS)
        friend class test::FeederSystemTest;
        using DriveMotor = trap::mock::motor::DjiM2006Mock;
        #else
        using DriveMotor = trap::motor::DjiM2006;
        #endif
            /**
             * roundsPerRevolution cannot be negative or zero which would cause corruption.
             * feedRate - this is the starting rounds per second
             * motorConfig - this is the configuration of the feeder motor
             */
            struct Config
            {
                int roundsPerRevolution;
                Hertz feedRate;
                RPM unjamSpeed;
                DriveMotor::Config motorConfig;
            };

            FeederSystem(Drivers& drivers, const Config& config);

            /**
             * How many rounds per second the system feed when turned on.
             * This cannot be negative in order to prevent damage.
             */
            void setFeedRate(const Hertz& FeedRate);

            void feedOn();
            void feedOff();

            void unjamOn();
            void unjamOff();

            /**
             * Check if the feed system is feeding ammo or not.
             */
            bool getActiveStatus();

            void update();
            void initialize();
        private:
            static constexpr int16_t mk_firingOutput{10'000};
            static constexpr int16_t mk_stopMotorOutput{0};
            RPM feedRateToRPM();
            const int mk_roundsPerRevolution;
            Hertz m_feedRate;
            const RPM m_unjamSpeed;
            DriveMotor m_motor;

            bool m_activeStatus{false};

            static constexpr RPM mk_stillSpeed{0.0};
        };
    }
}
#endif