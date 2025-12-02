#pragma once

#include "counter_chassis_field_yaw.hpp"
#include "telemetry/adapter/iangular_position_adapter.hpp"
#include "telemetry/adapter/iangular_velocity_adapter.hpp"

#include "wrap/trap/motor/dji_motor_aliases.hpp"
#include "wrap/trap/motor/dji_gm6020.hpp"
#include "driver/drivers.hpp"

namespace fang::turret
{

class Gm6020CounterChassisFieldYaw : public CounterChassisFieldYaw<trap::motor::DjiMotorOutput>
{
public:
    using Motor = trap::motor::DjiGM6020;
    using CounterYaw = CounterChassisFieldYaw<trap::motor::DjiMotorOutput>;

    struct Config
    {
        Motor::Config motorConfig;
        CounterYaw::Config fieldYawConfig;
    };

    Gm6020CounterChassisFieldYaw(
        Drivers& drivers,
        std::unique_ptr<Imu> chassisImu,
        std::unique_ptr<telemetry::IAngularVelocity> baseVelocityYawSensor,
        const Config& config
    ):
        CounterYaw{make(drivers, std::move(chassisImu), std::move(baseVelocityYawSensor), config)}
    {}

private:
    CounterYaw make(
        Drivers& drivers,
        std::unique_ptr<Imu> chassisImu,
        std::unique_ptr<telemetry::IAngularVelocity> baseVelocityYawSensor,
        const Config& config
    )
    {
        auto motor{
            std::make_unique<Motor>(
                drivers,
                config.motorConfig
            )
        };

        auto positionTelemetry{
            std::make_unique<telemetry::IAngularPositionAdapter>(
                *motor
            )
        };

        auto velocityTelemetry{
            std::make_unique<telemetry::IAngularVelocityAdapter>(
                *motor
            )
        };

        return CounterYaw{
            std::move(motor),
            std::move(positionTelemetry),
            std::move(velocityTelemetry),
            std::move(baseVelocityYawSensor),
            std::move(chassisImu),
            config.fieldYawConfig
        };
    }
};
}