#pragma once
#include "control/turret/gimbal/field_gimbal/field_gimbal.hpp"
#include "control/turret/gimbal/pitch/basic_field_pitch_system/gm6020_cascade_field_pitch.hpp"
#include "control/turret/gimbal/yaw/counter_chassis_field_yaw/gm6020_counter_chassis_field_yaw.hpp"
#include "control/turret/gimbal/yaw/counter_yaw_modder/imu_chassis_yaw_adapter.hpp"
#include "control/turret/gimbal/yaw/chassis_field_yaw_system/gm6020_cascade_chassis_yaw.hpp"

#include "wrap/trap/communication/sensors/imu.hpp"
namespace fang::turret
{
    class PierceFieldGimbal : public FieldGimbal
    {
    public:
        using PitchSystem = GM6020CascadeFieldPitch;
        using YawSystem   = Gm6020CounterChassisFieldYaw;
        using Imu = trap::communication::sensors::Imu;
        struct Config
        {
            PitchSystem::Config pitchSystemConfig;
            YawSystem::Config yawSystemConfig;

        };
        PierceFieldGimbal(Drivers& drivers, const Config& config):
            FieldGimbal
            {
                drivers,
                std::make_unique<PitchSystem>(drivers, config.pitchSystemConfig),
                std::make_unique<YawSystem>(
                    drivers,
                    std::make_unique<Imu>(drivers.bmi088),
                    std::make_unique<telemetry::ImuChassisYawVelocityAdapter>(
                        std::make_unique<Imu>(drivers.bmi088)
                    ),
                    config.yawSystemConfig
                )
            }
        {}

        virtual ~PierceFieldGimbal() {}
    };
}