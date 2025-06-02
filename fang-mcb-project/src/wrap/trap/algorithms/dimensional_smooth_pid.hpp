#ifndef FANG_ROBOTICS_MCB_TRAP_SMOOTH_PID_HPP
#define FANG_ROBOTICS_MCB_TRAP_SMOOTH_PID_HPP
#include "units.h"

#include "tap/algorithms/smooth_pid.hpp"

namespace trap
{
    namespace algorithms
    {
        /**
         * DO NOT USE
         * This will require the use of units::lenth::meters instead of units::length::meter_t
         * The control unit is the unit that is used to change the system
         * The error unit is the unit that the system takes as an input
         * The time unit is unit for the passage of time
         * 
         * For proportional control, the input is a quantity of unit
         * error. The output has to be of unit control.
         * Therefore, the unit of proportional has to be control/error
         * Because in each discrete step, k*error = control
         * 
         * In dimensional analysis terms
         * (control_t/error_t) * error_t = control_t
         * 
         * The next two feel a bit more unituitive, but bear
         * So integral control multiplies the error times the time.
         * So the units of the I*(integral(e(t))) must be the control unit
         * 
         * The unit of the I is (control_t/(error_t * time_t))
         * Since the integral's unit is error_t * time_t, it cancels out
         * when multipliedwith the I constant, resulting in the output being control
         * 
         * Finally, the unit of the D constant mus be (control_t)* (time_t/error_t)
         * The derivative takes the error and divides it by time, therefore, the units
         * from the derivative term is (error_t/time_t) which cancels with the (time_t/error_t)
         * leaving the control_t
         * 
         * For most people, this distincting is irrelevant. For the analytical minds, it might help
         * with interpreting the values. The most intuitive is proportional control: "how much control must
         * I apply for every error?"
         * 
         * Integral: "How much control should I apply for how long the error remains times the error itself?"
         * (Look up absement)
         * 
         * Derivative: "How much control should I apply for rate of change of the error itself?"
         * (A bit more intuitive than integral)
         */
        template<typename RawControlUnit, typename RawErrorUnit, typename RawTimeUnit>
        class DimensionalSmoothPid
        {
        public:
            using ControlUnit = units::unit_t<RawControlUnit>;
            using ErrorUnit = units::unit_t<RawErrorUnit>;
            using TimeUnit = units::unit_t<RawTimeUnit>;

            using PUnit = units::compound_unit<RawControlUnit, units::inverse<RawErrorUnit>>;
            using IUnit = units::compound_unit<RawControlUnit, units::inverse<RawErrorUnit>, units::inverse<RawTimeUnit>>;
            using DUnit = units::compound_unit<RawControlUnit, RawTimeUnit, units::inverse<RawErrorUnit>>;
            
            using ErrorDerivativeUnit = units::compound_unit<RawErrorUnit, units::inverse<RawTimeUnit>>;

            using IntegralAccumulationUnit = units::compound_unit<RawErrorUnit, RawTimeUnit>;
            /**
             * p - proportional constant
             * i - integral constant
             * d - derivative constant
             * maxIntegralAccumulation - clamps integral
             * maxOutput - maximum output
             * errorDerivativeFloor - minimum error for the derivative to kick in
             * errorDeadzone  - within [-errorDeadzone, and errorDeadzone], the error will be considered 0.
             */
            struct Config
            {
            public:
                PUnit p;
                IUnit i;
                DUnit d;
                IntegralAccumulationUnit maxIntegralAccumulation;
                ControlUnit maxOutput;
                ErrorUnit errorDerivativeFloor;
                ErrorUnit errorDeadzone = ErrorUnit{0.0};
                float tQDerivativeKalman = 1.0f;
                float tRDerivativeKalman = 0.0f;
                float tQProportionalKalman = 1.0f;
                float tRProportionalKalman = 0.0f;

                /**
                 * Mercy constructor
                 */
                Config(double p, double i, double d, double maxIntegralAccumulation, double maxOutput, double errorDerivativeFloor,
                       double errorDeadzone = 0.0, double tQDerivativeKalman = 1.0, double tRDerivativeKalman = 0.0, tRProportionalKalman = 1.0)
                : Config{PUnit{p} IUnit{i}, DUnit{d}, IntegralAccumulationUnit{maxIntegralAccumulation}, ControlUnit{maxOutput}, ErrorUnit{errorDerivativeFloor},
                  ErrorUnit{errorDeadzone}, tQDerivativeKalman, tRDerivativeKalman, tQProportionalKalman, tRProportionalKalman}
                {}
            }

            DimensionalSmoothPid(const Config& config);
            /**
             * error - how much error
             * This wrapper automatically calculates how much the error has changed
             * and the amount of time which has passed between calls
             */
            runController(ErrorUnit error);
            /**
             * Manually include delta time (this is for testing purposes but may bear use to future testers)
             */
            runController(ErrorUnit error, ErrorDerivativeUnit errorDerivative, TimeUnit deltaTime);
        private:
            tap::algorithms::SmoothPid m_smoothPid;
        };
    }
}
#endif