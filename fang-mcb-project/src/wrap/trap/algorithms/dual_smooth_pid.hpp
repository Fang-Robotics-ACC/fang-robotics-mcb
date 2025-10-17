#pragma once

#include "smooth_pid.hpp"
#include "util/chrono/simple_timer.hpp"

namespace trap::algorithms
{
    template<typename MainType, typename IntermediateType, typename OutputType, typename TimeType>
    /**
     * Cascading PID
     * 
     * MainError is the type for the beginning and main targeted value
     * IntermediateError is the type that is in the middl
     * 
     * e.g. Radians which then output a target RPM which outputs an abstract Motoroutput
     * 
     * The main target is the radians, but the target for the intermediate error
     * is give by the first PID
     */
    class DualSmoothPid
    {
    public:
        using MainPid = SmoothPid<MainType, IntermediateType, TimeType>;
        using IntermediatePid = SmoothPid<IntermediateType, OutputType, TimeType>; 
        struct Config
        {
            MainPid::Config mainPidConfig;
            IntermediatePid::Config intermediatePidConfig;
            IntermediateType mainPidInitialValue;
            OutputType intermediatePidInitialValue;
        };

        DualSmoothPid(const Config& config)
            :
            mainPid_{config.mainPidConfig, config.mainPidInitialValue},
            intermediatePid_{config.intermediatePidConfig, config.intermediatePidConfig}
        {
        }

        /**
         * @param mainCurent - current value of main 
         * @param intermediateCurrent  - current value of intermediate type
         * 
         * This wrapper automatically calculates how much the error has changed
         * and the amount of time which has passed between calls
         */
        OutputType runController(const MainType& mainCurrent, const IntermediateType& intermediateCurrent)
        {
            const TimeType kDeltaTime{static_cast<TimeType>(runControllerTimer_.getDurationAndReset())};
            return runController(mainCurrent, intermediateCurrent, kDeltaTime):
        }

        /**
         * Allows unit testing an manual time determination see the main version
         * for parameter information
         */
        OutputType runController
        (
            const MainType& mainError,
            const IntermediateType& intermediateError,
            const TimeType& deltaTime
        )
        {
            const IntermediateType kIntermediateTarget{mainPid_.runController(mainError), deltaTime};

            return intermediatePid_.runController(intermediateError, deltaTime);
        }

    private:
        MainPid mainPid_;
        IntermediatePid intermediatePid_;

        MainType mainTarget_{}; 
        fang::chrono::SimpleTimer runControllerTimer_{};
    };
}