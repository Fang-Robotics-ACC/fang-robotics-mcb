#pragma once

#include "rail/turret/gimbal/ifield_gimbal_info.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::turret
{
    using IFieldGimbalInfo = rail::turret::IFieldGimbalInfo<Radians>;
}