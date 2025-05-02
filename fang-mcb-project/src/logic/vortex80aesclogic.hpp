#ifndef VORTEX_80A_ESC_LOGIC_H_LSDJKFLSKEFJF_YEET
#define VORTEX_80A_ESC_LOGIC_H_LSDJKFLSKEFJF_YEET
#include "unitaliases.hpp"

namespace logic
{
    namespace motors
    {
        class Vortex80AEscLogic
        {
        public:
            /**
             * Returns a duty cycle from
             * [0,1] (percentage in decimal form)
             * 
             * The Vortex motor controller expects
             * a pulse from 1ms to 2ms with 1ms
             * corresponding to the lowest possible input, 0 and
             * 2ms corresponding to the highest input, 1.
             * 
             * In unidirectional, the speed percentage range
             * is [0,1]
             * Therefore, 0.5 would correspond to a motor moving
             * 50% of the maximum speed
             * 
             * In bidirectional, the range is [-1,1]
             * Therefore, 0.5 would correspond to a motor being still.
             * 0 would correspond to a motor running at full speed in reverse
             */
            double adaptedDutyCycle(double rangePercentage, Hertz pinFrequency);
        private:
            // Note that in bidirectional mode, the minimum period would
            // correspond to the motor going in full speed reverse
            // But in unidirectional mode, it would mean a still motor
            const Milliseconds mk_maxRangePeriod {2.0};
            const Milliseconds mk_minRangePeriod {1.0};
        };
    }
}
#endif