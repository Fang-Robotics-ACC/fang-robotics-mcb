#ifndef UNIT_ALIASES_HPP_SDLDDFLKJSKFJELKFJAS
#define UNIT_ALIASES_HPP_SDLDDFLKJSKFJELKFJAS
#define UNIT_LIB_DEFAULT_TYPE float
#include "units.h"
using NewtonMeters = units::torque::newton_meter_t;
using Watts = units::power::watt_t;
using Meters = units::length::meter_t;
using MetersPerSecond = units::velocity::meters_per_second_t;
using RPM = units::angular_velocity::revolutions_per_minute_t;
using Volts = units::voltage::volt_t;
using RPMPerVolt = units::compound_unit<RPM, units::inverse<Volts>>; //Used in Motor Constants
#endif