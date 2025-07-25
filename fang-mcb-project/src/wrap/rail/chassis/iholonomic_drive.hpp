#ifndef FANG_ROBOTICS_MCB_SRC_WRAP_RAIL_CHASSIS_IHOLONOMIC_DRIVE_HPP
#define FANG_ROBOTICS_MCB_SRC_WRAP_RAIL_CHASSIS_IHOLONOMIC_DRIVE_HPP
#include "util/physics/data/velocity_2d.hpp"
#include "wrap/units/units_alias.hpp"
#include "rail/chassis/iholonomic_drive.hpp"

namespace fang::chassis
{
    using IHolnomicDrive = rail::chassis::IHolonomicDrive<physics::Velocity2D, RPM>;
}
#endif