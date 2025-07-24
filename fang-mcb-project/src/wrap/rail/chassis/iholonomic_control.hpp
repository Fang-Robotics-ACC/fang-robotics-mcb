#ifndef FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSIS_I_HOLONOMIC_CONTROL_HPP
#define FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSIS_I_HOLONOMIC_CONTROL_HPP
#include "util/physics/data/velocity_2d.hpp"
#include "wrap/units/units_alias.hpp"
#include "rail/chassis/iholonomic_control.hpp"

namespace fang::chassis
{
    using IHolonomicControl = rail::chassis::IHolonomicControl<physics::Velocity2D, RPM>;
}
#endif