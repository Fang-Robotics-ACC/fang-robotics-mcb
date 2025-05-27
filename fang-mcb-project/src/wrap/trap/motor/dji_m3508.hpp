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
            /**
             * drivers - the drivers struct
             * motorId - the motor controller id
             * canBus - the can bus the motor controller is on
             * name - the name of the motor for the controller menu
             * gearRatio - the ratio of input revolutions per output revolution 
             */
            DjiM3508(Drivers& drivers, tap::motor::MotorId motorId, tap::can::CanBus canBus,
                     const char* name, bool inverted, bool currentControl, double gearRatio);
            /**
             * It must be called for the motor to properly function.
             */
            void initialize();

            /**
             * The desired motor output. It must be limited to a 16 bit int.
             */
            void setDesiredOutput(int16_t desiredOutput);

            /**
             * true if a can message has been received within the last
             * MOTOR_DISCONNECT_TIME.
             */
            bool isMotorOnline() const;

            /**
             * Returns the reported temperature in degrees.
             * The temperature was provided in an int8_t
             */
            Celsius getTemperature() const;
        private:
            tap::motor::DjiMotor m_djiMotor;
        };
    }
}
#endif