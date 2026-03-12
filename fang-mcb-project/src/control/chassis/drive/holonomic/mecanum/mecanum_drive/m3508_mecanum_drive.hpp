#pragma once

#include "mecanum_drive.hpp"
#include "control/chassis/drive/quad_drive/data/quad_collection.hpp"

// add different quad drive here
#include "/home/jagger/Projects/fang-robotics-mcb/fang-mcb-project/src/control/chassis/drive/quad_drive/power_quad_drive/m3508_power_quad_drive.hpp"
#include "control/chassis/drive/quad_drive/power_quad_drive/ultra_mk2_power_quad_drive.hpp"

#include "driver/drivers.hpp"
#include "driver/motor/repeat_robotics/repeat_ultra_mk2.hpp"


//add my motors here
#include "taproot/src/tap/motor/dji_motor.hpp"
#include "taproot/src/tap/motor/m3508_constants.hpp"

//MOTOR
#include "/home/jagger/Projects/fang-robotics-mcb/fang-mcb-project/src/wrap/trap/motor/dji_m3508.hpp"
 
/*
REMEMBER TO FIX PATH TO THESE vv */
#include "/home/jagger/Projects/fang-robotics-mcb/fang-mcb-project/src/wrap/trap/motor/dji_motor.hpp"
#include "/home/jagger/Projects/fang-robotics-mcb/fang-mcb-project/src/wrap/trap/motor/dji_motor.hpp"
/*
REMEMBER TO FIX PATH TO THESE ^^ */


#include "wrap/trap/control/chassis/power_limiter.hpp"

namespace fang::chassis
{
    class M3508MecanumDrive : public MecanumDrive
    {
    public:
        using Motor = trap::motor::DjiM3508;
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
                drivers,// create m3508 powerQuadDrive
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