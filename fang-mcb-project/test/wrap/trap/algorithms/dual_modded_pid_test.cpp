#include "wrap/trap/algorithms/dual_modded_pid.hpp"
#include "wrap/trap/algorithms/dual_cascade_pid.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <wrap/units/units_alias.hpp>

namespace trap::algorithms::dualModdedPidTest
{
using Pid = DualModdedPid<double, double, double, Milliseconds>;
using SmoothPidMain = DualCascadePid<double, double, double, Milliseconds>;

constexpr Pid::MainPid::Config kGeneralPidConfig
{
    .kp = 1.0,
    .ki = 0.0,
    .kd = 0.0,
    .maxOutput = 10000
};

constexpr Pid::Config kConfig
{
    .mainPidConfig = kGeneralPidConfig,
    .intermediatePidConfig = kGeneralPidConfig,
};

constexpr SmoothPidMain::Config kConfigSmooth
{
    .mainPidConfig = kGeneralPidConfig,
    .intermediatePidConfig = kGeneralPidConfig,
    .mainPidInitialValue = 0.0,
    .intermediatePidInitialValue = 0.0
};

/**
 * The pid will not have a modder and utilize the default
 * 
 * Run both controllers and ensure they both provide the same output
 */
TEST(ModdedPid, nullModdingMatch)
{
    SmoothPidMain expected{kConfigSmooth};
    Pid modded{kConfig};

    const double kMainCurrent{10.0};
    const Milliseconds kDeltaTime{10};
    const double kTarget{1};
    const double kIntermediate{10};

    expected.setTarget(kTarget);
    modded.setTarget(kTarget);

    const double kExpectedOutput{expected.runController(kMainCurrent, kIntermediate, kDeltaTime)};
    const double kOutput{modded.runController(kMainCurrent, kIntermediate, kDeltaTime)};
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

    SmoothPidMain expected{kConfigSmooth};
    Pid modded{
        kConfig,
        std::make_unique<AddOneModder>(),
        std::make_unique<AddOneModder>()
    };

    const double kMainCurrent{10.0};
    const Milliseconds kDeltaTime{10};
    const double kTarget{1};
    const double kIntermediate{10};

    expected.setTarget(kTarget);
    modded.setTarget(kTarget);

    // Add one to each stage
    const double kExpectedOutput{expected.runController(kMainCurrent, kIntermediate, kDeltaTime) + 2.0};
    const double kOutput{modded.runController(kMainCurrent, kIntermediate, kDeltaTime)};
    EXPECT_DOUBLE_EQ(kExpectedOutput, kOutput);
}
}