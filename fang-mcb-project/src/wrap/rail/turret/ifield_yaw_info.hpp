#pragma once

#include "rail/turret/gimbal/ifield_yaw_info.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::turret
{
    using IFieldYawInfo = rail::turret::IFieldYawInfo<Radians>;
}