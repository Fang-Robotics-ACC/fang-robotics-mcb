#ifndef FANG_ROBOTICS_MCB_TRAP_SMOOTH_PID_HPP
#define FANG_ROBOTICS_MCB_TRAP_SMOOTH_PID_HPP
#include "tap/algorithms/smooth_pid.hpp"
#include "util/chrono/simple_timer.hpp"

namespace trap
{
    namespace algorithms
    {
        /** This will require the use of units::lenth::meters instead of units::length::meter_t
         * The control unit is the unit that is used to change the system
         * The error unit is the unit that the system takes as an input
         * The time unit is unit for the passage of time
         */
        template<typename ErrorUnit, typename ControlUnit, typename TimeUnit>
        class SmoothPid
        {
        public:

            using ControlUnit = units::unit_t<RawControlUnit>;
            using ErrorUnit = units::unit_t<RawErrorUnit>;
            using TimeUnit = units::unit_t<RawTimeUnit>;
            using ErrorDerivativeUnit = units::compound_unit<RawErrorUnit, units::inverse<RawTimeUnit>>;

            //A bit of cheating
            using Config = tap::algorithms::SmoothPidConfig;

            SmoothPid(const Config& config, ErrorUnit initialLastError = ErrorUnit{0})
            : m_smoothPid{config}, m_lastError{initialLastError}
            {
            }

            /**
             * error - how much error
             * This wrapper automatically calculates how much the error has changed
             * and the amount of time which has passed between calls
             */
            ControlUnit runController(ErrorUnit error)
            {
                const TimeUnit deltaTime{m_runControllerTimer.getDurationAndReset()};
                const ErrorUnit deltaError{error - m_lastError};
                const ErrorDerivativeUnit errorDerivative{error / deltaTime};
                runController(error, errorDerivative, deltaTime);
            }

            /**
             * Manually include delta time (this is for testing purposes but may bear use to future testers)
             */
            ControlUnit runController(ErrorUnit error, ErrorDerivativeUnit errorDerivative, TimeUnit deltaTime)
            {
                float result {m_smoothPid.runController(static_cast<float>(error), estatic_cast<float>(errorDerivative), static_cast<float>(deltaTime))};
                return ControlUnit{result};
            }

        private:
            tap::algorithms::SmoothPid m_smoothPid;
            ErrorUnit m_lastError{0};
            chrono::SimpleTimer m_runControllerTimer{};
        };

    }
}
#endif