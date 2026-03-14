#pragma once

#include "rail/turret/gimbal/ifield_yaw_telemetry.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::turret
{
    using IFieldYawTelemetry = rail::turret::IFieldYawTelemetry<Radians>;
}