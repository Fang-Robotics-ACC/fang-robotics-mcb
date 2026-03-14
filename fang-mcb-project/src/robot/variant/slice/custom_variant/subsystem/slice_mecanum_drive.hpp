#pragma once

#include "control/chassis/drive/holonomic/mecanum/mecanum_drive/ultra_mk2_mecanum_drive.hpp"
#include "wrap/trap/communication/sensors/imu.hpp"
#include "wrap/trap/control/chassis/power_limiter.hpp"

namespace fang::chassis
{
    class PierceMecanumDrive : public UltraMk2MecanumDrive
    {
    public:
        using PowerLimiter = trap::control::chassis::PowerLimiter;
        using MotorConfigs = QuadCollection<Motor::Config>;

        struct Config
        {
            MotorConfigs motorConfigs;
            PowerLimiter::Config powerLimiterConfig;
            FieldMecanumLogic::Config fieldMecanumConfig;
            Hertz chassisPwmFrequency;
            tap::gpio::Pwm::Timer pwmTimer;
        };

        PierceMecanumDrive
        (
            Drivers& drivers,
            const Config& config
        ):
            UltraMk2MecanumDrive
            {
                drivers,
                std::make_unique<PowerLimiter>(drivers.refSerial, config.powerLimiterConfig),
                std::make_unique<trap::communication::sensors::Imu>(drivers.bmi088),
                {config.motorConfigs, config.fieldMecanumConfig}
            },
            pwm_{drivers.pwm},
            chassisPwmFrequency_{config.chassisPwmFrequency},
            pwmTimer_{config.pwmTimer}
        {}

        void setUpPwm()
        {
            //Taproot stores the frequency in an integral form.  The frequency
            //is recast to Hertz in case it is stored in a different unit before
            //it stripped of dimensional analysis
            const static auto kConvertedFreq {static_cast<uint32_t>(Hertz{chassisPwmFrequency_})}; 
            pwm_.setTimerFrequency(pwmTimer_, kConvertedFreq);
        }

        void initialize() override
        {
            UltraMk2MecanumDrive::initialize();
            setUpPwm();
        }
        //Minor additions can be kept in a header
    private:
        tap::gpio::Pwm& pwm_;
        const Hertz chassisPwmFrequency_;
        const tap::gpio::Pwm::Timer pwmTimer_;
    };
}