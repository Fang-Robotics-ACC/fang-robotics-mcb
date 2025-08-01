#pragma once

#include "control/chassis/drive/holonomic/mecanum/mecanum_drive/ultra_mk2_mecanum_drive.hpp"
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
            }
        {}
    };
}