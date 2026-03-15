#pragma once

#include "control/chassis/drive/holonomic/mecanum/mecanum_drive/m3508_mecanum_drive.hpp"

#include "wrap/trap/communication/sensors/imu.hpp"
#include "wrap/trap/control/chassis/power_limiter.hpp"

namespace fang::chassis
{
    class SliceMecanumDrive : public M3508MecanumDrive
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

        SliceMecanumDrive
        (
            Drivers& drivers,
            const Config& config
        ):
            M3508MecanumDrive
            {
                drivers,
                std::make_unique<PowerLimiter>(drivers.refSerial, config.powerLimiterConfig),
                std::make_unique<trap::communication::sensors::Imu>(drivers.bmi088),
                {config.motorConfigs, config.fieldMecanumConfig}
            }
        {}

    };
}