#pragma once

#include "driver/motor/pid/dual_cascade_motor/dual_cascade_motor.hpp"
#include "wrap/units/units_alias.hpp"
#include "wrap/rail/motor/iposition_motor.hpp"
#include "wrap/trap/algorithms/ring_radians.hpp"

namespace fang::motor
{
    /**
     * This provides access for Position Motors
     * 
     * Purpose to change: Interfacing generic dual cascade
     * with IPositionMotor
     */
    template <typename Output, typename Intermediate>
    class DualCascadePosition
        :
        public DualCascadeMotor<Output, trap::algorithms::RingRadians, Intermediate>,
        virtual public IPositionMotor
    {
    public:
        using CascadeMotor = DualCascadeMotor<Output, trap::algorithms::RingRadians, Intermediate>;
        using Config = CascadeMotor::Config;

        using CascadeMotor::CascadeMotor;

		void setTargetPosition(const Radians& position) override
        {
            CascadeMotor::setTarget(position);
        }
    };
}