#pragma once

#include "chassis_field_yaw_system.hpp"

#include "driver/drivers.hpp"
#include "wrap/trap/motor/dji_gm6020.hpp"

namespace fang::turret
{
    class GM6020FieldYawSystem : public ChassisFieldYawSystem
    {
    public:
        using Motor = trap::motor::DjiGM6020;
        struct Config
        {
            Motor::Config motorConfig;
            Radians yawError;
        };
        GM6020FieldYawSystem(Drivers& drivers, std::unique_ptr<Imu> chassisImu, const Config& config):
            ChassisFieldYawSystem
            (
                std::make_unique<Motor>(drivers, config.motorConfig),
                std::move(chassisImu),
                ChassisFieldYawSystem::Config{config.yawError}
            )
        {}
    };
}