#include "control/turret/ammo_booster/flywheel_system/flywheel_system.hpp"
#include "wrap/units/units_alias.hpp"
#include "test/mock/rail/rail_motor_mocks.hpp"

#include <gtest/gtest.h>
#include <tuple>

using namespace fang;
class FlywheelSpeedTest : public ::testing::TestWithParam<std::tuple<Meters, MetersPerSecond,RPM>>
{
public:
using FlywheelSystem = fang::turret::FlywheelSystem;
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
    auto motor{std::make_unique<motor::ISpeedMotorMock>()};
    motor::ISpeedMotorMock& motorView {*motor}; //Get access to call status
    EXPECT_CALL(motorView, setTargetSpeed(expectedRPMCall));

    FlywheelSystem flywheelSystem{std::move(motor),flywheelConfig};

    flywheelSystem.setTargetRimSpeed(targetRimSpeed);
}

INSTANTIATE_TEST_SUITE_P(zeroTest, FlywheelSpeedTest,
                         testing::Values(std::make_tuple(1_m, 0_mps, 0_rad_per_s)));

INSTANTIATE_TEST_SUITE_P(scalingTest, FlywheelSpeedTest,
                         testing::Values(std::make_tuple(0.5_m, 1_mps, 2_rad_per_s)));

INSTANTIATE_TEST_SUITE_P(negativeScalingTest, FlywheelSpeedTest,
                         testing::Values(std::make_tuple(0.5_m, -1_mps, -2_rad_per_s)));
