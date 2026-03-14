#pragma once

#include "mecanum_drive.hpp"
#include "control/chassis/drive/quad_drive/data/quad_collection.hpp"


#include "src/control/chassis/drive/quad_drive/power_quad_drive/m3508_power_quad_drive.hpp"
#include "driver/drivers.hpp"

#include "wrap/trap/motor/dji_m3508_old.hpp"


#include "wrap/trap/control/chassis/power_limiter.hpp"

namespace fang::chassis
{
    class M3508MecanumDrive : public MecanumDrive
    {
    public:
        using Motor = trap::motor::DjiM3508Old;
        using PowerLimiter = trap::control::chassis::PowerLimiter;
        struct Config
        {
            QuadCollection<Motor::Config> motorConfigs;
            FieldMecanumLogic::Config fieldMecanumConfig;
        };

        M3508MecanumDrive
        (
            Drivers& drivers,
            std::unique_ptr<IPowerLimiterSystem> powerLimiter,
            std::unique_ptr<MecanumDrive::Imu> imu,
            const Config& config
        ):
            MecanumDrive
            {
                drivers,
                std::make_unique<M3508PowerQuadDrive>
                (
                    drivers,
                    std::move(powerLimiter),
                    config.motorConfigs
                ),
                std::move(imu),
                {config.fieldMecanumConfig}
            }
        {}

        virtual ~M3508MecanumDrive() {}
    };// M3508MecanumDrive

}