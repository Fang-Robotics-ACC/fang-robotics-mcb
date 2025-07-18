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
using Milliseconds = units::time::millisecond_t;
using RadiansPerSecond = units::angular_velocity::radians_per_second_t;
using Radians = units::angle::radian_t;
using Degrees = units::angle::degree_t;
using RawRadianMeters = units::compound_unit<units::angle::radians, units::length::meters>;
using RadianMeters = units::unit_t<RawRadianMeters>;
using RawRadianMetersPerSecond = units::compound_unit<RawRadianMeters, units::inverse<units::time::seconds>>;
using RadianMetersPerSecond = units::unit_t<RawRadianMetersPerSecond>;
using Celsius = units::temperature::celsius_t;
using Microseconds = units::time::microsecond_t;
//Must be used when doing calculations involving translating between linear and rotational kinematics
// "How many meters per radians" (meters/radians) * (radins / second) = meters/second
using RawRadians = units::angle::radians;
using RawMeters = units::length::meters;
using RawMetersPerRadians = units::compound_unit<RawMeters, units::inverse<RawRadians>>;
using MetersPerRadians = units::unit_t<RawMetersPerRadians>;
using Joules = units::energy::joule_t;
#endif
