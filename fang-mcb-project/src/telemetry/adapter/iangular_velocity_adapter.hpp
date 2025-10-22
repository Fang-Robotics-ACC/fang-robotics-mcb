#pragma once

#include "wrap/rail/telemetry/itelemetry.hpp"
#include "wrap/rail/telemetry/iangular_velocity_telemetry.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::telemetry
{
    /**
     * Allows specific telemetry classes to be used as basic
     * telemetry
     */
    class IAngularVelocityAdapter : public ITelemetry<RPM>
    {
    public:
        IAngularVelocityAdapter(const IAngularVelocity& telemetry) : telemetry_{telemetry}
        {
        }

        RPM getData() const override
        {
            return telemetry_.getAngularVelocity();
        }

    private:
        const IAngularVelocity& telemetry_;
    };
}