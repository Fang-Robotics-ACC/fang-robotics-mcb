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

//One of the few moments that I would use auto
//These constants do not alter anything numerically, but are useful when
//Performing operations that convert angular to linear velocity
//The unit resulting from multiplying radians per second and meters do
//not result in meters per second. It results in meters radians per second
//Which are incompatible units with velocity. This is a bit of a hack, however
//it gets the job done without causing too much of a mess.
//I am a bit hesitant to have it in the global namespace; however, it is limited and
//deals with patching syntax.
auto const k_antiRadians{1.0 / Radians{1.0}};
const Radians k_addRadians{1.0};
#endif