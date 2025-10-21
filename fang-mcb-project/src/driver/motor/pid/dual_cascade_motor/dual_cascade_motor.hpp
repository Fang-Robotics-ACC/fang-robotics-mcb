#pragma once

#include "wrap/rail/motor/ioutput_motor.hpp"
#include "wrap/rail/telemetry/itelemetry.hpp"

#include <memory>

namespace fang::motor
{
    /**
     * Template parameters:
     * Output - the output motor it accepts
     * Control - the type used for controlling
     * Intermediate - the type used in between controlling and outputting
     * (2nd pid)
     */
    template <typename Output, typename Control, typename Intermediate>
    class DualCascadeMotor
    {
    public:
        using ControlledMotor = IOutputMotor<Output>;
        using ControlTelemetry = telemetry::ITelemetry<Control>;
        using IntermediateTelemetry = telemetry::ITelemetry<Intermediate>;

        DualCascadeMotor
        (
            std::unique_ptr<ControlledMotor> motor,
            std::unique_ptr<ControlTelemetry> controlTelemetry,
            std::unique_ptr<IntermediateTelemetry> intermediateTelemetry>
        )
            :
            motor_{std::move(motor)},
            controlTelemetry_{std::move(controlTelemetry)},
            intermediateTelemetry_{std::move(intermediateTelemetry)}
        {
        }

    private:
        std::unique_ptr<ControlledMotor> motor_;
        std::unique_ptr<ControlTelemetry> controlTelemetry_;
        std::unique_ptr<IntermediateTelemetry> intermediateTelemetry_;
    };
}