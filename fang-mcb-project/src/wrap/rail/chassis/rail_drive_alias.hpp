#ifndef FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSIS_RAIL_DRIVED_ALIAS_HPP
#define FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSIS_RAIL_DRIVED_ALIAS_HPP
#include "rail/chassis/quad_drive_data.hpp"

namespace fang::chassis
{
    template<typename Data>
    using QuadDriveData = rail::chassis::QuadDriveData<Data>;
}
#endif