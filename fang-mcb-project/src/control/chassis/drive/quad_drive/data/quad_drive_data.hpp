#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DATA_QUAD_DRIVE_DATA_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DATA_QUAD_DRIVE_DATA_HPP
#include "wrap/rail/chassis/rail_drive_alias.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::chassis
{
    using AbstractQuadSpeeds = QuadDriveData<double>;
    using QuadRPM = QuadDriveData<RPM>;
    using QuadSpeedsRadPersec = QuadDriveData<RadiansPerSecond>;
}
#endif