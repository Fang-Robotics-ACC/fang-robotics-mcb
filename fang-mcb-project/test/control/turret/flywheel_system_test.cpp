#include "flywheel_system_test.hpp"

#include "unitaliases.hpp"

#include <gtest/gtest.h>
#include <tuple>


using namespace test;

using namespace units::literals;
TEST_P(FlywheelSpeedTest, basicTest)
{
    EXPECT_CALL(motor, setTargetSpeed(expectedRPMCall));

    flywheelSystem.setTargetRimSpeed(targetRimSpeed);
}

INSTANTIATE_TEST_SUITE_P(zeroTest, FlywheelSpeedTest,
                         testing::Values(std::make_tuple(1_m, 0_mps, 0_rad_per_s)));

INSTANTIATE_TEST_SUITE_P(scalingTest, FlywheelSpeedTest,
                         testing::Values(std::make_tuple(0.5_m, 1_mps, 2_rad_per_s)));

INSTANTIATE_TEST_SUITE_P(negativeScalingTest, FlywheelSpeedTest,
                         testing::Values(std::make_tuple(0.5_m, -1_mps, -2_rad_per_s)));
