#pragma once

#include "wrap/rail/telemetry/itelemetry.hpp"
#include "wrap/rail/telemetry/iangular_position_telemetry.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::telemetry
{
    /**
     * Allows specific telemetry classes to be used as basic
     * telemetry
     */
    class IAngularPositionAdapter : public ITelemetry<Radians>
    {
    public:
        IAngularPositionAdapter(const IAngularPosition& telemetry) : telemetry_{telemetry}
        {
        }

        Radians getData() const override
        {
            return telemetry_.getAngularPosition();
        }

    private:
        const IAngularPosition& telemetry_;
    };
}