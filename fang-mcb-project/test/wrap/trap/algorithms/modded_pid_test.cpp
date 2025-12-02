#include "wrap/trap/algorithms/modded_pid.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <wrap/units/units_alias.hpp>

namespace trap::algorithms::moddedPidTest
{
using Pid = ModdedPid<double, double, Milliseconds>;
using SmoothPidMain = SmoothPid<double, double, Milliseconds>;

constexpr Pid::Config kGeneralPidConfig
{
    .kp = 1.0,
    .ki = 0.0,
    .kd = 0.0,
    .maxOutput = 10000
};

/**
 * The pid will not have a modder and utilize the default
 * 
 * Run both controllers and ensure they both provide the same output
 */
TEST(ModdedPid, nullModdingMatch)
{
    SmoothPidMain expected{kGeneralPidConfig};
    Pid modded{kGeneralPidConfig};

    const double kError{10.0};
    const Milliseconds kDeltaTime{10};

    const double kExpectedOutput{expected.runController(kError, kDeltaTime)};
    const double kOutput{modded.runController(kError, kDeltaTime)};
    EXPECT_DOUBLE_EQ(kExpectedOutput, kOutput);
}

/**
 * The pid will not have a modder and utilize the default
 * 
 * Run both controllers and ensure they both provide the same output
 */
TEST(ModdedPid, simpleModding)
{
    class AddOneModder : public IPidModder<double>
    {
        double getModdedOutput(const double& output)
        {
            return output + 1;
        }
    };

    AddOneModder testModder{};

    SmoothPidMain expected{kGeneralPidConfig};
    Pid modded{kGeneralPidConfig, std::make_unique<AddOneModder>()};

    const double kError{10.0};
    const Milliseconds kDeltaTime{10};

    const double kRawExpectedOutput{expected.runController(kError, kDeltaTime)};
    const double kExpectedOutput{kRawExpectedOutput + 1.0};

    const double kOutput{modded.runController(kError, kDeltaTime)};
    EXPECT_DOUBLE_EQ(kExpectedOutput, kOutput);
}
}