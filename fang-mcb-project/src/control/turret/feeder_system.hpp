#ifndef FANG_ROBOTICS_MCB_FEEDER_SYSTEM_HPP
#define FANG_ROBOTICS_MCB_FEEDER_SYSTEM_HPP
#include "unitaliases.hpp"

#include "tap/motor/dji_motor.hpp"

#if defined(PLATFORM_HOSTED) && defined(ENV_UNIT_TESTS)
#include "mock/trap/motor/dji_m2006_mock.hpp"
#include "test/control/turret/feeder_system_test.hpp"
#else
#include "trap/motor/dji_m2006.hpp"
#endif


#include "drivers.hpp"

namespace control
{
    namespace turret
    {
        /**
         * This controls the Feeder Motor. update() must be periodically called
         * to update the motor's associated PID.
         */
        class FeederSystem
        {
        public:
        friend class test::FeederSystemTest;
        #if defined(PLATFORM_HOSTED) && defined(ENV_UNIT_TESTS)

        using DriveMotor = trap::mock::motor::DjiM2006Mock;
        #else
        using DriveMotor = trap::motor::DjiM2006;
        #endif
            struct Config
            {
                int roundsPerRevolution;
                Hertz feedRate;
                DriveMotor::Config motorConfig;
            };

            FeederSystem(Drivers& drivers, const Config& config);

            /**
             * How many rounds per second the system feed when turned on.
             */
            void setFeedRate(const Hertz& FeedRate);

            void feedOn();
            void feedOff();

            /**
             * Check if the feed system is feeding ammo or not.
             */
            bool getActiveStatus();

            void update();
        private:
            RPM feedRateToRPM();
            const int mk_roundsPerRevolution;
            Hertz m_feedRate;
            DriveMotor m_motor;

            bool m_activeStatus{false};

            static constexpr RPM mk_stillSpeed{0.0};
        };
    }
}
#endif