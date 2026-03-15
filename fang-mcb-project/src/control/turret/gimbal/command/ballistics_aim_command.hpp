#pragma once

#include "control/turret/gimbal/field_gimbal_subsystem.hpp"
#include "communication/cool_protocol/ibasic_target_listener.hpp"
#include "util/math/arithmetic/range.hpp"
#include "tap/algorithms/transforms/vector.hpp"

#include "wrap/rail/turret/igimbal_input.hpp"
#include "wrap/trap/communication/sensors/iimu.hpp"

#include "tap/control/command.hpp"

namespace fang::turret 
{
    /**
     * Unlike aim command, it takes the raw position instead of velocity.
     * Used for autonomous testing and as a precursor to general auto-aim commands
     */
    class BallisticsAimCommand : public tap::control::Command, public communication::IBasicTargetListener
    {
    public:
        struct Config
        {
            MetersPerSecond bulletVelocity;
        };
        BallisticsAimCommand(FieldGimbalSubsystem& gimbal, trap::communication::sensors::IImu& cameraOrientationImu, const Config& config);
        void basicTargetFound(const BasicTargetT& basicTarget) override;

        const char* getName() const override {return "Ballistic Aim";}
        void initialize() override;
        void execute() override;
        void end(bool interrupted) override;
        bool isFinished() const override;

    private:
        using Vector = tap::algorithms::transforms::Vector;
        using Transform = tap::algorithms::transforms::Transform;
        using Orientation = tap::algorithms::transforms::Orientation;
        using Position = tap::algorithms::transforms::Position;
        Vector cameraToGlobal(const Vector& cameraCoordinates) const;
        const Config config_;
        FieldGimbalSubsystem& gimbal_;
        trap::communication::sensors::IImu& cameraOrientationImu_;
        BasicTargetT currentTarget_{};
    };
}