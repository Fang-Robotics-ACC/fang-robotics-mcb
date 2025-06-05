#ifndef FANG_ROBOTICS_MCB_FLYWHEEL_SYSTEM_HPP
#define FANG_ROBOTICS_MCB_FLYWHEEL_SYSTEM_HPP
#include "unitaliases.hpp"
#include "tap/motor/dji_motor.hpp"
#include "trap/motor/dji_m3508.hpp"
#include "mock/trap/motor/dji_m3508_mock.hpp"
#include "drivers.hpp"

namespace control
{
    namespace turret
    {
        /**
         * This is meant to abstract a single flywheel of a given radius.
         * It's update function must be periodically called in order for the
         * motors to be called. This is not a taproot subsystem, it is meant
         * to not be used by taproot's command scheduler. This is to provide
         * the turret subsystem a "subsubsystem", which is not supported by taproot.
         * 
         */
        class FlywheelSystem
        {
        public:
        #if defined(PLATFORM_HOSTED) && defined(ENV_UNIT_TESTS)

        using DriveMotor = trap::mock::motor::DjiM3508Mock;
        #else
        using DriveMotor = trap::motor::DjiM3508;
        #endif
            struct Config
            {
                Meters radius;
                DriveMotor::Config motorConfig;
            };

            FlywheelSystem(Drivers& drivers, const Config& config);

            void setTargetRimSpeed(const MetersPerSecond& rimSpeed);
            void update() const;
        private:
            RPM RimSpeedToMotorSpeed(const MetersPerSecond& rimSpeed) const;
            MetersPerRadians m_radius;
            DriveMotor m_motor;
        };
    }
}
#endif