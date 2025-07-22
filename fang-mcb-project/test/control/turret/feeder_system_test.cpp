#include "control/turret/system/feeder_system.hpp"

#include "wrap/units/units_alias.hpp"

#include <gtest/gtest.h>
#include <tuple>

/*
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

        control::turret::FeederSystem feederSystem{drivers, control::k_feederSystemConfig};
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
//If the wheel does one shot per revolution, and we need one shot per second, then it must done 1 revolution per second
INSTANTIATE_TEST_SUITE_P(oneTest, FeederSystemTest, testing::Values(std::make_tuple(1, 1_Hz, 1_rps)));

//If the wheel does 11 shots per revolution, and we need one shot per second, then it must done 11 revolutions per second
INSTANTIATE_TEST_SUITE_P(multiShotRevolutionTest, FeederSystemTest, testing::Values(std::make_tuple(1, 1_Hz, 1_rps)));

//If the wheel does 1 shot per revolution, and we need 120 shot per second, then it must done 120 revolutions per second
INSTANTIATE_TEST_SUITE_P(largeFPSTest, FeederSystemTest, testing::Values(std::make_tuple(1, 11_Hz, 11_rps)));

//Mixed test based on the previous principles
INSTANTIATE_TEST_SUITE_P(mixedTest, FeederSystemTest,
    testing::Values(std::make_tuple(10, 10_Hz, 1_rps),
                    std::make_tuple(100, 10_Hz, 0.1_rps),
                    std::make_tuple(123, 1_Hz, (1.0_rps/123.0)),
                    std::make_tuple(100, 412_Hz, 4.12_rps),
                    std::make_tuple(500, 10_Hz, (10.0_rps/500.0))));
*/