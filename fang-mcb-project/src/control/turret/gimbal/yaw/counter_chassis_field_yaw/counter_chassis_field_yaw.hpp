#pragma once
#include "control/turret/gimbal/yaw/chassis_field_yaw_system/chassis_field_yaw_system.hpp"
#include "driver/motor/pid/modded_cascade_position/modded_cascade_position.hpp"
#include "control/turret/gimbal/yaw/counter_yaw_modder/counter_yaw_modder.hpp"

namespace fang::turret
{

/**
 * This is slightly different from other pitch systems
 * in the fact that it takes a dualCascadePosition instead of a position
 * motor.
 * 
 * This is able to add compensation for the tilt
 * 
 * It also requires telemetry for
 */
template<typename Output>
class CounterChassisFieldYaw : public ChassisFieldYawSystem 
{
public:
    using ModdedCascadeMotor = motor::ModdedCascadePosition<Output, RPM>;
    using ControlTelemetry = telemetry::ITelemetry<Radians>;
    using IntermediateTelemetry = telemetry::ITelemetry<RPM>;
    struct Config
    {
        ChassisFieldYawSystem::Config chassisFieldYawConfig;
        CounterYawModder::Config counterYawConfig;
    };

    CounterChassisFieldYaw(
        std::unique_ptr<motor::IOutputMotor<Output>> motor,
        std::unique_ptr<ControlTelemetry> controlTelemetry,
        std::unique_ptr<IntermediateTelemetry> intermediateTelemetry,
        std::unique_ptr<telemetry::IAngularVelocity> baseVelocityYawSensor,
        std::unique_ptr<Imu> imu,
        const Config& config
    ):
        ChassisFieldYawSystem 
        {
            std::make_unique<ModdedCascadeMotor>(
                std::move(motor),
                std::move(controlTelemetry),
                std::move(intermediateTelemetry),
                std::make_unique<CounterYawModder>(std::move(baseVelocityYawSensor), config.counterYawConfig),
                std::make_unique<trap::algorithms::NullPidModder<Output>>()
            ),
            std::move(imu),
            config.pitchSystemConfig
        }
    {}

private:
};
}