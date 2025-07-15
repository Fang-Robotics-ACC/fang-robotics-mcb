#include "unitaliases.hpp"
#include "control/turret/system/blueprint/flywheel_system.hpp"
#include "test/mock/rail/rail_motor_mocks.hpp"

#include <gtest/gtest.h>
#include <tuple>

class FlywheelSpeedTest : public ::testing::TestWithParam<std::tuple<Meters, MetersPerSecond,RPM>>
{
public:
using FlywheelSystem = control::turret::FlywheelSystem;
    const Meters radius{std::get<0>(GetParam())};
    const MetersPerSecond targetRimSpeed{std::get<1>(GetParam())};
    const RPM expectedRPMCall{std::get<2>(GetParam())};

    const FlywheelSystem::Config flywheelConfig
    {
        .radius = radius
    };

    Drivers drivers;
};

using namespace units::literals;
TEST_P(FlywheelSpeedTest, basicTest)
{


    mock::motor::ISpeedMotorMock motor{};
    FlywheelSystem flywheelSystem{motor, flywheelConfig};

    EXPECT_CALL(motor, setTargetSpeed(expectedRPMCall));

    flywheelSystem.setTargetRimSpeed(targetRimSpeed);
}

INSTANTIATE_TEST_SUITE_P(zeroTest, FlywheelSpeedTest,
                         testing::Values(std::make_tuple(1_m, 0_mps, 0_rad_per_s)));

INSTANTIATE_TEST_SUITE_P(scalingTest, FlywheelSpeedTest,
                         testing::Values(std::make_tuple(0.5_m, 1_mps, 2_rad_per_s)));

INSTANTIATE_TEST_SUITE_P(negativeScalingTest, FlywheelSpeedTest,
                         testing::Values(std::make_tuple(0.5_m, -1_mps, -2_rad_per_s)));
