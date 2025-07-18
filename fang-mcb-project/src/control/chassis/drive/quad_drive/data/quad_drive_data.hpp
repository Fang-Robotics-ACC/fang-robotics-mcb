#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DATA_QUAD_DRIVE_DATA_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DATA_QUAD_DRIVE_DATA_HPP
#include "wrap/rail/chassis/rail_drive_alias.hpp"
#include "unitaliases.hpp"
namespace chassis
{
    using AbstractWheelSpeeds = QuadDriveData<double>;
    using WheelSpeeds = QuadDriveData<RPM>;
    using QuadDriveWheelSpeedsRadPersec = QuadDriveData<RadiansPerSecond>;
}
#endif