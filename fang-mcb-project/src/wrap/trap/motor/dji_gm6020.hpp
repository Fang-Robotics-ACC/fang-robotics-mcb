#ifndef FANG_ROBOTICS_MCB_TRAP_DJI_M3508_HPP
#define FANG_ROBOTICS_MCB_TRAP_DJI_M3508_HPP
#include "unitaliases.hpp"
#include "wrap/trap/motor/dji_motor_aliases.hpp"
#include "trap/algorithms/wrapped_radians.hpp"

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
        class DjiGM6020 
        {
        public:
            struct Config
            {
                tap::motor::MotorId motorId;
                tap::can::CanBus canBus;
                const char* name;
                bool inverted;
                double gearRatio;
                DjiSpeedPid::Config speedPidConfig;
                bool currentControl = true;
            };
            DjiGM6020(Drivers& drivers, const Config& config);
            /**
             * drivers - the drivers struct
             * motorId - the motor controller id
             * canBus - the can bus the motor controller is on
             * name - the name of the motor for the controller menu
             * gearRatio - the ratio of input revolutions per output revolution 
             * pid config: make sure the maxOutput does not exceed DjiM3508 k_maxOutput.
             * This would lead to undefined behavior. An assertion has been placed to prevent
             * the code from continuing.
             */
            DjiGM6020(Drivers& drivers, tap::motor::MotorId motorId, tap::can::CanBus canBus,
                     const char* name, bool inverted, double gearRatio, const DjiSpeedPid::Config& speedConfig, bool currentControl);


            /**
             * Must be called regularly to update the motor pid and set the motor output
             */
            void update();

            /**
             * Sets the desired speed for the pid to target
             */
            void setTargetPosition(const Radians& targetPosition);

            /**
             * Returns the last reported RPM from CAN
             */
            Radians getPosition() const;

            /**
             * It must be called for the motor to properly function.
             */
            void initialize();

            /**
             * The desired motor output. It must be limited to a 16 bit int.
             */
            void setDesiredOutput(DjiMotorOutput desiredOutput);

            /**
             * true if a can message has been received within the last
             * MOTOR_DISCONNECT_TIME.
             */
            bool isMotorOnline() const;

            /**
             * Returns the reported temperature in celsius.
             * The temperature was provided in an int8_t
             */
            Celsius getTemperature() const;

            tap::can::CanBus getCanBus() const;

            const char* getName() const;

        static const DjiMotorOutput k_maxOutput{tap::motor::DjiMotor::MAX_OUTPUT_GM6020};
        private:
            tap::motor::DjiMotor m_djiMotor;
            DjiSpeedPid m_speedPid;
            double m_gearRatio;

            trap::algorithms::WrappedRadians m_targetPosition{Radians{0.0}};
        };
    }
}
#endif