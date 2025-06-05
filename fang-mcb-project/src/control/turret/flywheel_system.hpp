#ifndef FANG_ROBOTICS_MCB_FLYWHEEL_SYSTEM_HPP
#define FANG_ROBOTICS_MCB_FLYWHEEL_SYSTEM_HPP
#include "unitaliases.hpp"
#include "tap/motor/dji_motor.hpp"
#include "trap/motor/dji_m3508.hpp"
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
            using DriveMotor = trap::motor::DjiM3508;
            class Config
            {
                Meters radius;
                DriveMotor::Config motorConfig;
            };

            FlywheelSystem(Drivers& drivers, const Config& config);

            void setDesiredRimSpeed(const RPM& rimSpeed);
            void update();
        private:
            DriveMotor m_motor;
        };
    }
}
#endif