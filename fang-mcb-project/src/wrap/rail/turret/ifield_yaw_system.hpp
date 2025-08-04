#pragma once

#include "rail/turret/gimbal/ifield_yaw_system.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::turret
{
    using IFieldYawSystem = rail::turret::IFieldYawSystem<Radians>;
}