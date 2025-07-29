#ifndef FANG_ROBOTICS_MCB_WRAP_RAIL_CASSIS_QUAD_DATA_ALIAS_HPP
#define FANG_ROBOTICS_MCB_WRAP_RAIL_CASSIS_QUAD_DATA_ALIAS_HPP
#include "quad_drive_data.hpp"
#include "wrap/units/units_alias.hpp"
namespace fang::chassis
{
    using AbstractQuadSpeeds = QuadDriveData<double>;
    using QuadRPM = QuadDriveData<RPM>;
    using QuadSpeedsRadPersec = QuadDriveData<RadiansPerSecond>;
}
#endif