#pragma once

#include "wrap/rail/motor/ioutput_motor.hpp"
#include "wrap/rail/telemetry/itelemetry.hpp"
#include "wrap/rail/system/isystem.hpp"

#include "wrap/trap/algorithms/dual_modded_pid.hpp"

#include "wrap/units/units_alias.hpp"

#include <memory>

namespace fang::motor
{
    /**
     * This functions exactly as DualCascadeMotor
     * (taking an output motor and applying PID based
     * on the telemetry it recieves)
     * 
     * This has an optional modders for the PID for feedForward.
     * 
     * For example, the output can be modded or the intermediate pid (target speed
     * in most cases) can be given an additoinal speed target ahead of time
     * 
     * Template parameters:
     * Output - the output motor it accepts
     * Control - the type used for controlling and intermediate calculations of Pid
     * Intermediate - the type used in between controlling and outputting
     * (2nd pid)
     */
    template
        <
        typename Output,
        typename Control,
        typename Intermediate,
        typename Time = Seconds,
        typename MainError = Control,
        typename IntermediateError = Intermediate 
        >
    class ModdedCascadeMotor : virtual public system::ISystem
    {
    public:
        using ControlledMotor = IOutputMotor<Output>;
        using ControlTelemetry = telemetry::ITelemetry<Control>;
        using IntermediateTelemetry = telemetry::ITelemetry<Intermediate>;
        using Pid = trap::algorithms::DualModdedPid
            <
            Control,
            Intermediate,
            Output,
            Time,
            MainError,
            IntermediateError
            >;
        using Config = Pid::Config;
        using MainModder = Pid::MainModder;
        using IntermediateModder = Pid::IntermediateModder;

        ModdedCascadeMotor(
            const Config& config,
            std::unique_ptr<ControlledMotor> motor,
            std::unique_ptr<ControlTelemetry> controlTelemetry,
            std::unique_ptr<IntermediateTelemetry> intermediateTelemetry,
            std::unique_ptr<MainModder> mainModder = std::make_unique<trap::algorithms::NullPidModder<Intermediate>>(),
            std::unique_ptr<IntermediateModder> intermediateModder  = std::make_unique<trap::algorithms::NullPidModder<Output>>()
        ):
            pid_{config, std::move(mainModder), std::move(intermediateModder)},
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
            syncMotorToPid();
            motor_->update();
        }

        /**
         * Back door function used for testing until
         * we DI chrono based classes, too.
         */
        void update(const Time& delta)
        {
            const Output kOutput
            {
                pid_.runController(
                    controlTelemetry_->getData(),
                    intermediateTelemetry_->getData(),
                    delta
                )
            };
            motor_->setTargetOutput(kOutput);
            motor_->update();
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
                pid_.runController(
                    controlTelemetry_->getData(),
                    intermediateTelemetry_->getData()
                )
            };
            motor_->setTargetOutput(kOutput);
        }
    };
}