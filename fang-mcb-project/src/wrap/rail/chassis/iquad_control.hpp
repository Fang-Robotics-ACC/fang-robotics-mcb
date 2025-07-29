#ifndef FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSIS_IQUAD_CONTROL_HPP
#define FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSIS_IQUAD_CONTROL_HPP

#include "rail/chassis/iquad_control.hpp"
#include "control/chassis/drive/quad_drive/data/quad_drive_data.hpp"

namespace fang::chassis
{
    using IQuadControl = rail::chassis::IQuadControl<QuadRPM>;
}
#endif