#ifndef UNIT_ALIASES_HPP_SDLDDFLKJSKFJELKFJAS
#define UNIT_ALIASES_HPP_SDLDDFLKJSKFJELKFJAS
#include "units.h"

using NewtonMeters = units::torque::newton_meter_t;
using Watts = units::power::watt_t;
using Meters = units::length::meter_t;
using MetersPerSecond = units::velocity::meters_per_second_t;
using RPM = units::angular_velocity::revolutions_per_minute_t;
using Volts = units::voltage::volt_t;
using RawRPM = units::angular_velocity::revolutions_per_minute;
using RawVolts = units::voltage::volts;
using RawRPMPerVolt = units::compound_unit<RawRPM, units::inverse<RawVolts>>; //Used in Motor Constants
using RPMPerVolt = units::unit_t<RawRPMPerVolt>;
using Hertz = units::frequency::hertz_t;
using Seconds = units::time::second_t;
#endif