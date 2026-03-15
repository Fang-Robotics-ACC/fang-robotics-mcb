#pragma once

#include "rail/turret/gimbal/ifield_pitch_telemetry.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::turret
{
    using IFieldPitchTelemetry = rail::turret::IFieldPitchTelemetry<Radians>;
}