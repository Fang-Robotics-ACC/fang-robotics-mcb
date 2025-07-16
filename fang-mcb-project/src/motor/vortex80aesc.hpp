#ifndef FANG_ROBOTICS_MCB_VORTEX_80A_ESC_LOGIC_H
#define FANG_ROBOTICS_MCB_VORTEX_80A_ESC_LOGIC_H
#include "unitaliases.hpp"

#include "util/math/cool_lerp.hpp"
#include "data/vector2d.hpp"

#include "motor/data/directionality.hpp"

#include "wrap/trap/communication/pwm_data.hpp"

#include "tap/communication/gpio/pwm.hpp"
namespace motor
{
    /**
     * Driver for the Vortex80AEsc involving sending various signals and speed ranges.
     */
    class Vortex80AEsc
    {
    public:
        using Directionality = ::motor::Directionality;
        Vortex80AEsc(tap::gpio::Pwm& pwm, const trap::gpio::PwmData& pwmData, const Directionality& directionality = Directionality::BIDIRECTIONAL);
        /**
         * Sends the appropriate arming signal
         */
        void sendArmingSignal();
        /**
         * This will lock the code for half a second, sending the armin signal
         * This is mainly used for tests. If you have a lot of motors,
         * the code will lock up for that given period.
         */
        void armingRoutine();
        void setSpeed(double speedRangePercentage);
        /**
         * This is how long the pwm signal stays high each cycle.
         * You snhould not exceed the cycle period.
         */
        void setPulseDuration(const Microseconds& duration);
        void setDirectionality(const Directionality& directionality);
        Directionality getDirectionality() const;
    private:
        tap::gpio::Pwm& m_pwm;
        trap::gpio::PwmData m_pwmData;
        const Microseconds mk_cyclePeriod;
        //Maximum and minimum speed range percentages
        const double mk_bidirectionalMin {-1.0};
        const double mk_bidirectionalMax {1.0};
        const double mk_unidirectionalMin {0.0};
        const double mk_unidirectionalMax {1.0};
        Directionality m_directionality;
        const Microseconds mk_bidirectionalArmingSignal{1500};
        const Microseconds mk_unidirectionalArmingSignal{1000};
        const Milliseconds mk_armingPeriod{500};
        //Map speed range percentage of -1.0 to 1000 us
        const math::CoolLerp::Vector2D mk_bidirectionalPoint1{-1.0, 1000.0};
        //Map speed rnage percentage of 1.0 to 2000 us
        const math::CoolLerp::Vector2D mk_bidirectionalPoint2{1.0, 2000.0};
        math::CoolLerp m_bidirectionalMap{mk_bidirectionalPoint1, mk_bidirectionalPoint2};
        //Map speed range percentage of 0.0 to 1000 us
        const math::CoolLerp::Vector2D mk_unidirectionalPoint1{0.0, 1000.0};
        //Map speed rnage percentage of 1.0 to 2000 us
        const math::CoolLerp::Vector2D mk_unidirectionalPoint2{1.0, 2000.0};
        math::CoolLerp m_unidirectionalMap{mk_unidirectionalPoint1, mk_unidirectionalPoint2};
        Microseconds calculateUnidirectionalPeriod(double speedRangePercentage) const;
        Microseconds calculateBidirectionalPeriod(double speedRangePercentage) const;
        Microseconds calculatePeriod (double speedRangePercentage) const;
        void pwmWrite(double dutyCycle);
    };
}
#endif