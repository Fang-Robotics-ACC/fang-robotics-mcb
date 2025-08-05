#pragma once

#include "rail/turret/gimbal/ifield_gimbal.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::turret
{
    using IFieldGimbal = rail::turret::IFieldGimbal<Radians>;
}