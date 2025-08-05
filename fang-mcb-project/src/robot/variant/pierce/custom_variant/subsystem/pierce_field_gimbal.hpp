#pragma once
#include "control/turret/gimbal/field_gimbal/field_gimbal.hpp"
#include "control/turret/gimbal/yaw/chassis_field_yaw_system/gm6020_chassis_field_yaw_system.hpp"
#include "control/turret/gimbal/pitch/basic_field_pitch_system/gm6020_basic_field_pitch.hpp"
namespace fang::turret
{
    class PierceFieldGimbal : public FieldGimbal
    {
    public:
        using PitchSystem = GM6020BasicFieldPitch;
        using YawSystem   = GM6020FieldYawSystem;
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
                std::make_unique<YawSystem>(drivers, config.yawSystemConfig)
            }
        {}

    };
}