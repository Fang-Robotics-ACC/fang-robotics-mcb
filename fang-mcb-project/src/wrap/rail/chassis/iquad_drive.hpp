#ifndef FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSIS_IQUAD_DRIVE_HPP
#define FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSIS_IQUAD_DRIVE_HPP

#include "rail/chassis/iquad_drive.hpp"
#include "quad_data_alias.hpp"

namespace fang::chassis
{
    using IQuadDrive = rail::chassis::IQuadDrive<QuadRPM>;
}
#endif