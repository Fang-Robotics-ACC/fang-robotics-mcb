#pragma once

#include "chassis_field_yaw_system.hpp"
#include "driver/drivers.hpp"
#include "driver/motor/pid/dual_cascade_position/dual_cascade_gm6020.hpp"

namespace fang::turret
{
    class GM6020CascadeFieldYaw : public ChassisFieldYawSystem
    {
    public:
        using Motor = motor::DualCascadeGm6020;
        struct Config
        {
            Motor::Config motorConfig;
            ChassisFieldYawSystem::Config yawSystemConfig;
        };
        GM6020CascadeFieldYaw(Drivers& drivers, std::unique_ptr<Imu> chassisImu, const Config& config):
            ChassisFieldYawSystem 
            {
                std::make_unique<Motor>(drivers, config.motorConfig),
                std::move(chassisImu),
                config.yawSystemConfig
            }
        {}
    };
}