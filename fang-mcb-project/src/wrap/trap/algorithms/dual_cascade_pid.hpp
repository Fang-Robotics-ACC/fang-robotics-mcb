#pragma once

#include "smooth_pid.hpp"
#include "util/chrono/simple_timer.hpp"

namespace trap::algorithms
{
    /**
     * Cascading PID
     * 
     * MainType is the type for the beginning and main targeted value
     * Intermediate is the type that is in the middle
     * Output is the type of the calculated value
     * 
     * MainError and IntermediateError is a custom override for utilizing types
     * which override arithmetic (wrapped float types). They should be convertible or constructible
     * from and to MainType and IntermediateType respectively
     * 
     * Error is calculated with target - current. So any
     * overload of the operator- will allow for custom behavior 
     * 
     * e.g. Radians which then output a target RPM which outputs an abstract Motoroutput
     * 
     * The main target is the radians, but the target for the intermediate error
     * is give by the first PID
     */
    template
    <
        typename MainType,
        typename IntermediateType,
        typename OutputType,
        typename TimeType,
        typename MainError = MainType,
        typename IntermediateError = IntermediateType
    >
    class DualCascadePid
    {
    public:
        using MainPid = SmoothPid<MainType, IntermediateType, TimeType>;
        using IntermediatePid = SmoothPid<IntermediateType, OutputType, TimeType>; 
        struct Config
        {
            MainPid::Config mainPidConfig;
            IntermediatePid::Config intermediatePidConfig;
            MainType mainPidInitialValue;
            IntermediateType intermediatePidInitialValue;
        };

        DualCascadePid(const Config& config)
            :
            mainPid_{config.mainPidConfig, config.mainPidInitialValue},
            intermediatePid_{config.intermediatePidConfig, config.intermediatePidInitialValue}
        {
        }

        /**
         * @param mainCurent - current value of main 
         * @param intermediateCurrent  - current value of intermediate type
         * 
         * WARNING: THIS IS DIFFERENT FROM STANDARD PID API
         * This wrapper automatically calculates how much the error has changed
         * and the amount of time which has passed between calls
         */
        OutputType runController(const MainType& mainCurrent, const IntermediateType& intermediateCurrent)
        {
            const TimeType kDeltaTime{static_cast<TimeType>(runControllerTimer_.getDurationAndReset())};
            return runController(mainCurrent, intermediateCurrent, kDeltaTime);
        }

        /**
         * Allows unit testing an manual time determination see the main version
         * for parameter information
         */
        OutputType  runController(
            const MainType& mainCurrent,
            const IntermediateType& intermediateCurrent,
            const TimeType& deltaTime
        )
        {
            const MainType kMainError{
                MainError{mainTarget_}
              - MainError{mainCurrent}
            };

            static MainType mainError{};
            mainError = kMainError;

            const IntermediateType kIntermediateTarget{
                mainPid_.runController(
                    kMainError,
                    deltaTime
                )
            };

            static IntermediateType intermediateTarget{};
            intermediateTarget = kIntermediateTarget;

            const IntermediateType kIntermediateError{
                IntermediateError{kIntermediateTarget}
              - IntermediateError{intermediateCurrent}
            };

            static IntermediateType intermediateError{};
            intermediateError = kIntermediateError;

            const OutputType kOutput{
                intermediatePid_.runController(
                    kIntermediateError,
                    deltaTime
                )
            };

            static OutputType output{};
            output = kOutput;

            return kOutput; 
        }

        void setTarget(const MainType& mainTarget)
        {
            mainTarget_ = mainTarget;
        }
    private:
        MainPid mainPid_;
        IntermediatePid intermediatePid_;

        MainType mainTarget_{}; 
        fang::chrono::SimpleTimer runControllerTimer_{};
    };
}