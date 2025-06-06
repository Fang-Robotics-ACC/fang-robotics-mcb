#include "feeder_system_test.hpp"

#include "unitaliases.hpp"

#include <gtest/gtest.h>
#include <tuple>


using namespace test;

using namespace units::literals;
TEST_P(FeederSystemTest, basicTest)
{
    EXPECT_CALL(motor, setTargetSpeed(expectedRPMCall));

    feederSystem.feedOn();
}

INSTANTIATE_TEST_SUITE_P(zeroTest, FeederSystemTest, testing::Values(std::make_tuple(1, 0_Hz, 0_rpm)));