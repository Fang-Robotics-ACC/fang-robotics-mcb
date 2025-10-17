#pragma once

#include "wrap/units/units_alias.hpp"
#include "rail/telemetry/iangular_position_telemetry.hpp"

namespace fang::telemetry
{
    using IAngularPosition = rail::telemetry::IAngularPosition<Radians>;
}