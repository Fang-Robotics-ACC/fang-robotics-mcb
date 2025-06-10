#ifndef FANG_ROBOTICS_MCB_TRAP_DJI_M2006_HPP
#define FANG_ROBOTICS_MCB_TRAP_DJI_M2006_HPP
#include "unitaliases.hpp"
#include "wrap/trap/motor/dji_motor_aliases.hpp"

#include "tap/motor/dji_motor.hpp"
#include "tap/motor/dji_motor_encoder.hpp"
#include "tap/communication/can/can_bus.hpp"
#include "tap/util_macros.hpp"
#include "drivers.hpp"

namespace trap
{
    namespace motor
    {
        /**
         * Wrapper for DJI motor for the DJI M3508 on a CAN bus
         */
        class DjiM2006
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
            };
            DjiM2006(Drivers& drivers, const Config& config);
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
            DjiM2006(Drivers& drivers, tap::motor::MotorId motorId, tap::can::CanBus canBus,
                     const char* name, bool inverted, double gearRatio, const DjiSpeedPid::Config& speedConfig);


            mockable ~DjiM2006() = default;

            /**
             * Must be called regularly to update the motor pid and set the motor output
             */
            mockable void update();

            /**
             * Sets the desired speed for the pid to target
             */
            mockable void setTargetSpeed(const RPM& targetSpeed);

            /**
             * Returns the last reported RPM from CAN
             */
            mockable RPM getSpeed() const;
            /**
             * It must be called for the motor to properly function.
             */
            mockable void initialize();

            /**
             * The desired motor output. It must be limited to a 16 bit int.
             */
            mockable void setDesiredOutput(DjiMotorOutput desiredOutput);

            /**
             * true if a can message has been received within the last
             * MOTOR_DISCONNECT_TIME.
             */
            mockable bool isMotorOnline() const;

            /**
             * Returns the reported temperature in celsius.
             * The temperature was provided in an int8_t
             */
            mockable Celsius getTemperature() const;

            mockable tap::can::CanBus getCanBus() const;

            mockable const char* getName() const;

        /// @brief Maximum output for C610 controller
        static constexpr DjiMotorOutput k_maxOutput{tap::motor::DjiMotor::MAX_OUTPUT_C610};

        /// @brief gear ratio of the gearbox that usually ships with the motor.
        static constexpr double k_factoryGearboxRatio{tap::motor::DjiMotorEncoder::GEAR_RATIO_M2006};
        private:
            tap::motor::DjiMotor m_djiMotor;
            DjiSpeedPid m_speedPid;
            const double m_gearRatio;

            RPM m_targetSpeed{0.0};

            //Current control in DjiMotor is for the GM6020s only
            //Setting it to true will mean the motor does not respond
            static constexpr bool mk_requiredCurrentMode{false};
        };
    }
}
#endif