#pragma once

#include "wrap/rail/motor/ioutput_motor.hpp"
#include "wrap/rail/telemetry/itelemetry.hpp"
#include "wrap/rail/system/isystem.hpp"

#include "wrap/trap/algorithms/dual_cascade_pid.hpp"

#include "wrap/units/units_alias.hpp"

#include <memory>

namespace fang::motor
{
    /**
     * Template parameters:
     * Output - the output motor it accepts
     * Control - the type used for controlling and intermediate calculations of Pid
     * Intermediate - the type used in between controlling and outputting
     * (2nd pid)
     */
    template <typename Output, typename Control, typename Intermediate>
    class DualCascadeMotor : public system::ISystem
    {
    public:
        using ControlledMotor = IOutputMotor<Output>;
        using ControlTelemetry = telemetry::ITelemetry<Control>;
        using IntermediateTelemetry = telemetry::ITelemetry<Intermediate>;
        using Pid = trap::algorithms::DualCascadePid<Control, Intermediate, Output, Seconds>;
        using Config = Pid::Config;

        DualCascadeMotor
        (
            const Config& config,
            std::unique_ptr<ControlledMotor> motor,
            std::unique_ptr<ControlTelemetry> controlTelemetry,
            std::unique_ptr<IntermediateTelemetry> intermediateTelemetry
        )
            :
            pid_{config},
            motor_{std::move(motor)},
            controlTelemetry_{std::move(controlTelemetry)},
            intermediateTelemetry_{std::move(intermediateTelemetry)}
        {
        }

        void initialize() override
        {
            motor_->initialize();
        }

        void update() override
        {
            motor_->update();
            syncMotorToPid();
        }

        void setTarget(const Control& control)
        {
            pid_.setTarget(control);
        }

    private:
        Pid pid_;
        std::unique_ptr<ControlledMotor> motor_;
        std::unique_ptr<ControlTelemetry> controlTelemetry_;
        std::unique_ptr<IntermediateTelemetry> intermediateTelemetry_;

        void syncMotorToPid()
        {
            const Output kOutput
            {
                pid_.runController
                (
                    controlTelemetry_->getData(),
                    intermediateTelemetry_->getData()
                )
            };
            motor_->setTargetOutput(kOutput);
        }
    };
}