#pragma once
#include "wrap/trap/drivers.hpp"
#include "wrap/trap/motor/dji_motor_aliases.hpp"
#include "wrap/trap/algorithms/wrapped_radians.hpp"
#include "wrap/units/units_alias.hpp"

#include "tap/communication/can/can_bus.hpp"
#include "tap/motor/dji_motor.hpp"
#include "tap/util_macros.hpp"

namespace trap::motor
{
    /**
     * Wrapper for DJI motor for the DJI M3508 on a CAN bus
     */
    class DjiMotor 
        :
        public IDjiOutputMotor
    {
    public:
        struct Config
        {
            tap::motor::MotorId motorId;
            tap::can::CanBus canBus;
            const char* name;
            bool inverted;
            DjiSpeedPid::Config speedPidConfig;
            bool currentControl = true;
            double externalEncoderGearRatio = 1.0;
        };

        DjiMotor(Drivers& drivers, const Config& config);

        /**
         * drivers - the drivers struct
         * motorId - the motor controller id
         * canBus - the can bus the motor controller is on. THIS CANNOT BE HIGHER THAN 4
         * name - the name of the motor for the controller menu
         * gearRatio - the ratio of input revolutions per output revolution 
         * pid config: make sure the maxOutput does not exceed DjiM3508 k_maxOutput.
         * This would lead to undefined behavior. An assertion has been placed to prevent
         * the code from continuing.
         * 
         * IMPORTANT if you are using GM6020
         * Why an ID not more thn 4? The GM6020 motor have their id offset by + 4 for some unholy DJI reason. (Ask their sages.)
         * Taproot decided to keep the regular motor ids, which meant that if you place MotorID::Motor1, it gets mapped to MotorID::Motor5
         * implicitly (irl, the GM6020 motor id needs to be set to 1, but the tapproot codewise motorId must be 5)
         * the enum does not go above Motor8, which means in order to access a Gm6020 with irl MotorId::Motor5, the codewise
         * motorId needs to be 9, which is not supported.
         * 
         * Fortunately, this ancient ritual does not need any blood sacrifice.
         * 
         * Long story short:: traproot currently uses the correct motor ID, taproot does not, so keep this in mind.
         * 
         * This oddity is a rite of passage as it is not really mentioned until the initiate tries to move a GM6020.
         * Although, as this is Fang Robotic's first year, and we had no elders to warn us of the dangers, we lost 4 hours to this ordeal.
         * 
         * However, taproot ended up keeping the regular motorID
         */
        DjiMotor(Drivers& drivers, tap::motor::MotorId motorId, tap::can::CanBus canBus,
                 const char* name, bool inverted, double externalEncoderGearRatio, const DjiSpeedPid::Config& speedConfig, bool currentControl);

        mockable ~DjiMotor() {};

        /**
         * It must be called for the motor to properly function.
         */
        void initialize() override;

        /**
         */
        void update() override;

        /**
         * Returns the last reported RPM from CAN
         */
        Radians getAngularPosition() const;

        /**
         * The desired motor output. It must be limited to a 16 bit int.
         */
		void setTargetOutput(const DjiMotorOutput& output) override;

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
    };
}