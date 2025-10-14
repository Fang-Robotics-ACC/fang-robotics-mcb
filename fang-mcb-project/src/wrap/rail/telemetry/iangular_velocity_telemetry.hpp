#pragma once

#include "wrap/units/units_alias.hpp"
#include "rail/telemetry/iangular_velocity_telemetry.hpp"

namespace fang::telemetry
{
    using IAngularVelocity = rail::telemetry::IAngularVelocity<RPM>;
}