#ifndef FANG_ROBOTICS_MCB_FLYWHEEL_SYSTEM_HPP
#define FANG_ROBOTICS_MCB_FLYWHEEL_SYSTEM_HPP
#include "unitaliases.hpp"
#include "trap/motor/dji_m3508.hpp"

namespace control
{
    namespace turret
    {
        class Flywheel
        {
        public:
            using DriveMotor = trap::motor::DjiM3508;
            void setDesiredRimSpeed(const RPM& rimSpeed);
            void update();
        };
    }
}
#endif