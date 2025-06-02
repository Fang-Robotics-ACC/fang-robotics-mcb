#include "gtest/gtest.h"
#include "wrap/trap/algorithms/smooth_pid.hpp"
#include "tap/algorithms/smooth_pid.hpp"
#include "unitaliases.hpp"
#include "units.h"

#include <tuple>

using SmoothPid = trap::algorithms::SmoothPid<RPM, int32_t>;
using namespace units::literals;
class SmoothPidTest :  public ::testing::TestWithParam<std::tuple<SmoothPid::Config, RPM, double, double>>
{
protected:
    const SmoothPid::Config config{std::get<0>(GetParam())};
    const RPM error{std::get<1>(GetParam())};
    const double errorDerivative{std::get<2>(GetParam())};
    const double deltaTime{std::get<3>(GetParam())};
    const Microseconds unitDeltaTime{deltaTime};
    SmoothPid trapSmoothPid{config};
    tap::algorithms::SmoothPid tapSmoothPid{config};
};

TEST_P(SmoothPidTest, pidMatchTest)
{
    int32_t trapOutput = trapSmoothPid.runController(error, errorDerivative, unitDeltaTime);
    int32_t tapOutput = tapSmoothPid.runController(static_cast<double>(error), errorDerivative, deltaTime);
    EXPECT_EQ(trapOutput, tapOutput);
}

INSTANTIATE_TEST_SUITE_P(basicTest, SmoothPidTest,
                         testing::Values(std::make_tuple(SmoothPid::Config{1,1,1}, 1.0_rpm, 1.0, 1.0),
                                         std::make_tuple(SmoothPid::Config{0,0,0}, 1.0_rpm, 1.0, 1.0),
                                         std::make_tuple(SmoothPid::Config{1.0,34,1345.0, 34.234}, 345.0_rpm, 1.0, 1.0)));

INSTANTIATE_TEST_SUITE_P(largeValue, SmoothPidTest,
                         testing::Values(std::make_tuple(SmoothPid::Config{34.345,122.34,345.5}, 1000.0_rpm, 1345.0, 100.0),
                                         std::make_tuple(SmoothPid::Config{345345,234234,1234324}, 345345.0_rpm, 345345.0, 345435.0),
                                         std::make_tuple(SmoothPid::Config{1.0,34,1345.0, 34.234}, 345.0_rpm, 1.0, 1.0)));

TEST(runtimeTimeDeltaTest, SmoothPid)
{
    SmoothPid smoothPid {SmoothPid::Config{}};
    smoothPid.runController(2342_rpm);
    smoothPid.runController(342_rpm);

    smoothPid.runController(2_rpm);
    smoothPid.runController(0_rpm);
}