#ifndef FANG_ROBOTICS_MCB_TRAP_DJI_M3508_HPP
#define FANG_ROBOTICS_MCB_TRAP_DJI_M3508_HPP
#include "unitaliases.hpp"

#include "tap/motor/dji_motor.hpp"
#include "tap/communication/can/can_bus.hpp"
#include "drivers.hpp"

namespace trap
{
    namespace motor
    {
        /**
         * Wrapper for DJI motor for the DJI M3508 on a CAN bus
         */
        class DjiM3508
        {
        public:
            struct Config
            {
                tap::motor::MotorId motorId;
                tap::can::CanBus canBus;
                const char* name;
                bool inverted;
                bool currentControl;
                double gearRatio;
            };
            DjiM3508(Drivers& drivers, const Config& config);
            DjiM3508(Drivers& drivers, tap::motor::MotorId motorId, tap::can::CanBus canBus,
                     const char* name, bool inverted, bool currentControl, double gearRatio);
            void initialize();
        private:
            tap::motor::DjiMotor m_djiMotor;
        };
    }
}
#endif