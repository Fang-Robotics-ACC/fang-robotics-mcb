#pragma once

#include "rail/turret/gimbal/ifield_pitch_system.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::turret
{
    using IFieldPitchSystem = rail::turret::IFieldPitchSystem<Radians>;
}