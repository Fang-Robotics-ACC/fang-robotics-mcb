#pragma once

#include "wrap/rail/telemetry/itelemetry.hpp"
#include "wrap/rail/telemetry/iangular_position_telemetry.hpp"
#include "wrap/units/units_alias.hpp"

#include "wrap/trap/algorithms/ring_radians.hpp"

namespace fang::telemetry
{
    /**
     * Allows specific telemetry classes to be used as basic
     * telemetry
     */
    class IAngularPositionAdapterRinged : public ITelemetry<trap::algorithms::RingRadians>
    {
    public:
        IAngularPositionAdapterRinged(const IAngularPosition& telemetry) : telemetry_{telemetry}
        {
        }

        trap::algorithms::RingRadians getData() const override
        {
            return telemetry_.getAngularPosition();
        }

    private:
        const IAngularPosition& telemetry_;
    };
}