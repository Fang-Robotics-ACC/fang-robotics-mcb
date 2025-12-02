#pragma once
#include "control/turret/gimbal/pitch/basic_field_pitch_system/basic_field_pitch_system.hpp"
#include "driver/motor/pid/modded_cascade_position/modded_cascade_position.hpp"
#include "control/turret/gimbal/pitch/tilt_pid_modder/tilt_pid_modder.hpp"

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
class CorrectingFieldPitch : public BasicFieldPitchSystem
{
public:
    using ModdedCascadeMotor = motor::ModdedCascadePosition<Output, RPM> ;
    struct Config
    {
        BasicFieldPitchSystem::Config pitchSystemConfig;
        TiltPidModder<Output>::Config tiltCorrectionConfig;
    };
    CorrectingFieldPitch(
        std::unique_ptr<motor::IOutputMotor<Output>> motor,
        std::unique_ptr<ControlTelemetry> controlTelemetry,
        std::unique_ptr<IntermediateTelemetry> intermediateTelemetry,
        const Config& config
    ):
        BasicFieldPitchSystem
        {
            std::make_unique<ModdedCascadeMotor>(
                std::move(motor),
                std::move(controlTelemetry),
                std::move(intermediateTelemetry),
                std::make_unique<trap::algorithms::NullPidModder<RPM>>(),
                std::make_unique<TiltPidModder<Output>>(config.tiltCorrectionConfig)
            ),
            config.pitchSystemConfig
        }
    {}

private:
};
}