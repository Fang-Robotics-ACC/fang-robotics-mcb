#include "control/turret/feeder_system.hpp"

#include "unitaliases.hpp"

#include <gtest/gtest.h>
#include <tuple>

using namespace units::literals;
namespace test
{
    class FeederSystemTest: public ::testing::TestWithParam<std::tuple<int, Hertz,RPM>>
    {
    public:

        const int roundsPerRevolution{std::get<0>(GetParam())};
        const Hertz feedRate{std::get<1>(GetParam())};
        const RPM expectedRPMCall{std::get<2>(GetParam())};

        Drivers drivers;
        const control::turret::FeederSystem::DriveMotor::DjiSpeedPid::Config defaultConfig 
        {
            1,
            1,
            1
        };
        const control::turret::FeederSystem::DriveMotor::Config motorConfig
        {
            tap::motor::MOTOR1,
            tap::can::CanBus::CAN_BUS1,
            "test motor",
            false,
            1.0,
            defaultConfig
        };
        const control::turret::FeederSystem::Config feederConfig{roundsPerRevolution, feedRate, motorConfig};

        control::turret::FeederSystem feederSystem{drivers, feederConfig};
        control::turret::FeederSystem::DriveMotor& motor{feederSystem.m_motor};
    };
}

using namespace test;

TEST_P(FeederSystemTest, basicTest)
{
    //This tests whether or not the desired speed sent into the motor given
    //how many rounds per rotation of the feeder gear and the desired fire rate
    EXPECT_CALL(motor, setTargetSpeed(expectedRPMCall));

    feederSystem.feedOn();
}

INSTANTIATE_TEST_SUITE_P(zeroTest, FeederSystemTest, testing::Values(std::make_tuple(1, 0_Hz, 0_rpm)));