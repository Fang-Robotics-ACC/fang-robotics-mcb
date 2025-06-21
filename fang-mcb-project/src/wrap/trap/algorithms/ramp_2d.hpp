#ifndef FANG_ROBOTICS_MCB_TRAP_ALGORITHMS_RAMP_2D_HPP
#define FANG_ROBOTICS_MCB_TRAP_ALGORITHMS_RAMP_2D_HPP
#include "trap/algorithms/ramp.hpp"
#include "mathaliases.hpp"
#include "data/vector2d.hpp"
namespace trap::algorithms
{
    template<typename ValueUnit, typename TimeUnit> 
    class Ramp2D
    {
    public:
        using Vector2D = data::math::Vector2D<ValueUnit>;

        /**
         * Ramp speed is how much value unit per time unit
         */
        Ramp2D(const Vector2D& initialValue, double rampSpeed)
        :   m_xRamp{initialValue.x, rampSpeed},
            m_yRamp{initialValue.y, rampSpeed},
            m_speed{rampSpeed}
        {
        }

        void setTarget(const Vector2D& target)
        {
            m_xRamp.setTarget(target.x);
            m_yRamp.setTarget(target.y);
            //If the target is already there, the delta is zero, leading to 
            //division by ZERO. This guards against that possibility
            if(!isTargetReached())
            {
                //We want the ramps to arrive at roughly the same time
                setRampSpeeds();
            }
        }

        Vector2D getTarget() const
        {
            return Vector2D{m_xRamp.getTarget(), m_yRamp.getTarget()};
        }

        /**
         * The speed of the ramps are only changed if a non-zero delta
         * between the curretn values and target values are different
         */
        void setSpeed(double speed)
        {
            m_speed = speed;
        }

        Vector2D getValue() const
        {
            return Vector2D{m_xRamp.getValue(), m_yRamp.getValue()};
        }

        bool isTargetReached() const
        {
            return m_xRamp.isTargetReached() && m_yRamp.isTargetReached();
        }

        void update() const
        {
            m_xRamp.update();
            m_yRamp.update();
        }

    private:
        /**
         * DANGER can trigger divide by zero if the magnitude between
         * the target and curretn value is zero.
         */
        void setRampSpeeds()
        {
            //We want the x and y ramps to arrive at roughly the same time
            const Vector2D delta{getTarget() - getValue()};
            const math::AbstractVector2D direction{delta.getUnitVector()};
            math::AbstractVector2D speeds{direction * m_speed};

            m_xRamp.setSpeed(speeds.x);
            m_yRamp.setSpeed(speeds.y);
        }
        Ramp<ValueUnit, TimeUnit> m_xRamp;
        Ramp<ValueUnit, TimeUnit> m_yRamp;
        double m_speed;
    };

}
#endif