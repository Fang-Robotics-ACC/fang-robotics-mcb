#pragma once

#include "rail/turret/gimbal/ifield_pitch_info.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::turret
{
    using IFieldPitchInfo = rail::turret::IFieldPitchInfo<Radians>;
}