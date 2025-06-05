#ifndef FANG_ROBOTICS_MCB_FLYWHEEL_SYSTEM_HPP
#define FANG_ROBOTICS_MCB_FLYWHEEL_SYSTEM_HPP
#include "unitaliases.hpp"
#include "tap/motor/dji_motor.hpp"
#include "trap/motor/dji_m3508.hpp"

namespace control
{
    namespace turret
    {
        /**
         * This is meant to abstract a single flywheel of a given radius.
         * It's update function must be periodically called in order for the
         * motors to be called
         */
        class Flywheel
        {
        public:
            using DriveMotor = trap::motor::DjiM3508;
            class Config
            {
                Meters radius;
                DriveMotor::Config motorConfig;
            };
            void setDesiredRimSpeed(const RPM& rimSpeed);
            void update();
        };
    }
}
#endif