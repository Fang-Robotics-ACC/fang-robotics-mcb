#ifndef FANG_ROBOTICS_MCB_TRAP_SMOOTH_PID_HPP
#define FANG_ROBOTICS_MCB_TRAP_SMOOTH_PID_HPP
#include "tap/algorithms/smooth_pid.hpp"
#include "util/chrono/simple_timer.hpp"
#include "configuration/unitaliases.hpp"

namespace trap
{
    namespace algorithms
    {
        /** This will require the use of units::lenth::meters instead of units::length::meter_t
         * The control unit is the unit that is used to change the system
         * The error unit is the unit that the system takes as an input
         * The time unit is unit for the passage of time
         */
        template<typename ErrorType, typename ControlType, typename TimeUnit>
        class SmoothPid
        {
        public:
            //A bit of cheating
            using Config = tap::algorithms::SmoothPidConfig;

            SmoothPid(const Config& config, ErrorType initialLastError = ErrorType{0})
            : m_smoothPid{config}, m_lastError{initialLastError}
            {
            }

            /**
             * error - how much error
             * This wrapper automatically calculates how much the error has changed
             * and the amount of time which has passed between calls
             */
            ControlType runController(ErrorType error)
            {
                const TimeUnit deltaTime{m_runControllerTimer.getDurationAndReset()};
                const ErrorType deltaError{error - m_lastError};
                const double errorDerivative{static_cast<double>(error) / deltaTime};
                return runController(error, errorDerivative, deltaTime);
            }

            /**
             * Manually include delta time (this is for testing purposes but may bear use to future testers)
             * For implementation purposes, the errorDerivative is stripped of any unit
             */
            ControlType runController(ErrorType error, double errorDerivative, TimeUnit deltaTime)
            {
                float result {m_smoothPid.runController(static_cast<float>(error), static_cast<float>(errorDerivative), static_cast<float>(deltaTime))};
                return static_cast<ControlType>(result);
            }

        private:
            tap::algorithms::SmoothPid m_smoothPid;
            ErrorType m_lastError{0};
            chrono::SimpleTimer m_runControllerTimer{};
        };

    }
}
#endif