#ifndef FANG_ROBOTICS_MCB_MUSIC_UNITS_HPP
#define FANG_ROBOTICS_MCB_MUSIC_UNITS_HPP
#include "units.h"
namespace units
{
    using BPM = compound_unit<inverse<units::time::minute_t>>;
}
#endif