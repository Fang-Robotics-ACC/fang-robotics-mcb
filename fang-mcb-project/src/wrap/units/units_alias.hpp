#ifndef FANG_ROBOTICS_MCB_WRAP_UNITS_UNIT_ALIAS_HPP
#define FANG_ROBOTICS_MCB_WRAP_UNITS_UNIT_ALIAS_HPP
#include "units.h"

//In order given in: https://github.com/nholthaus/units?tab=readme-ov-file#namespaces
// Length
using Meters = units::length::meter_t;
using RawMeters = units::length::meters;

// Time
using Seconds = units::time::second_t;
using Milliseconds = units::time::millisecond_t;
using Microseconds = units::time::microsecond_t;

// Angle
using Radians = units::angle::radian_t;
using RawRadians = units::angle::radians;
using Degrees = units::angle::degree_t;

// Tempearture
using Celsius = units::temperature::celsius_t;

// Frequency
using Hertz = units::frequency::hertz_t;

// Velocity
using MetersPerSecond = units::velocity::meters_per_second_t;

// Angular Velocity
using RPM = units::angular_velocity::revolutions_per_minute_t;
using RawRPM = units::angular_velocity::revolutions_per_minute;
using RadiansPerSecond = units::angular_velocity::radians_per_second_t;

//Energy
using Joules = units::energy::joule_t;

// Power
using Watts = units::power::watt_t;

// Voltage
using Volts = units::voltage::volt_t;
using RawVolts = units::voltage::volts;

// Torque
using NewtonMeters = units::torque::newton_meter_t;

// Custom section
// Motor
//KV Constant for brushless DC motors
using RawRPMPerVolt = units::compound_unit<RawRPM, units::inverse<RawVolts>>;
using RPMPerVolt = units::unit_t<RawRPMPerVolt>;

// Linear and rotation conversions
// Must be used when doing calculations involving translating between linear and rotational kinematics
// "How many meters per radians" (meters/radians) * (radins / second) = meters/second?"
using RawMetersPerRadians = units::compound_unit<RawMeters, units::inverse<RawRadians>>;
using MetersPerRadians = units::unit_t<RawMetersPerRadians>;
#endif