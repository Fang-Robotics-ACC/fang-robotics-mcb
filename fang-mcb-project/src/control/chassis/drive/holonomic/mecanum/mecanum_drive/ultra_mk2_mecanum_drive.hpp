#pragma once

#include "mecanum_drive.hpp"
#include "control/chassis/drive/quad_drive/data/quad_collection.hpp"
#include "control/chassis/drive/quad_drive/power_quad_drive/ultra_mk2_power_quad_drive.hpp"

#include "driver/drivers.hpp"
#include "driver/motor/repeat_robotics/ultra_mk2.hpp"

#include "wrap/trap/control/chassis/power_limiter.hpp"

namespace fang::chassis
{
    class UltraMk2MecanumDrive : public MecanumDrive
    {
    public:
        using Motor = motor::UltraMk2;
        using PowerLimiter = trap::control::chassis::PowerLimiter;
        struct Config
        {
            QuadCollection<Motor::Config> motorConfigs;
            FieldMecanumLogic::Config fieldMecanumConfig;
        };

        UltraMk2MecanumDrive
        (
            Drivers& drivers,
            std::unique_ptr<IPowerLimiterSystem> powerLimiter,
            std::unique_ptr<MecanumDrive::Imu> imu,
            const Config& config
        ):
            MecanumDrive
            {
                drivers,
                std::make_unique<UltraMk2PowerQuadDrive>
                (
                    drivers,
                    std::move(powerLimiter),
                    config.motorConfigs
                ),
                std::move(imu),
                {config.fieldMecanumConfig}
            }
        {}

        virtual ~UltraMk2MecanumDrive() {}
    };// UltraMk2MecanumDrive

}