#include "control/turret/gimbal_system.hpp"

#include "unitaliases.hpp"

#include <gtest/gtest.h>
#include <tuple>
#include "test/unit_matcher.h"

using namespace units::literals;
namespace test
{
    /**
     * This class is to simply provide private member access to multiple test classes
     * So that we can have variants
     */
    class GimbalSystemTest
    {
    public:
        using GimbalSystem = control::turret::GimbalSystem;
        using PositionMotor = GimbalSystem::PositionMotor;

        GimbalSystemTest(const GimbalSystem::Config& config) : gimbalSystem{drivers, config} {}
        Drivers drivers;
    public:
        GimbalSystem gimbalSystem;
        PositionMotor& pitchMotor{gimbalSystem.m_pitchMotor};
        PositionMotor& yawMotor{gimbalSystem.m_yawMotor};

    static constexpr GimbalSystem::PositionMotor::DjiSpeedPid::Config k_defaultPidConfig 
    {
        1,
        1,
        1
    };
    static constexpr GimbalSystem::PositionMotor::Config k_defaultMotorConfig 
    {
        tap::motor::MOTOR1,
        tap::can::CanBus::CAN_BUS1,
        "test motor",
        false,
        1.0,
        k_defaultPidConfig 
    };
    };

    class GimbalPitchTest: public ::testing::TestWithParam<std::tuple<Radians, Radians, Radians, Radians>>
    {
    public:
        const Radians pitchAngle{std::get<0>(GetParam())};
        const Radians expectedPitchCall{std::get<1>(GetParam())};
        Radians minPitch{std::get<2>(GetParam())};
        Radians maxPitch{std::get<3>(GetParam())};
    };
}


using namespace test;

TEST_P(GimbalPitchTest, basicPitchTest)
{
    const GimbalSystemTest::GimbalSystem::Config gimbalConfig
    {
        minPitch,
        maxPitch,
        GimbalSystemTest::k_defaultMotorConfig,
        GimbalSystemTest::k_defaultMotorConfig
    };

    GimbalSystemTest test{gimbalConfig};
    GimbalSystemTest::GimbalSystem& gimbal{test.gimbalSystem};

    //This tests the pitch clamping functionality
    EXPECT_CALL(test.pitchMotor, setTargetPosition((expectedPitchCall, testing::UnitEq(expectedPitchCall))));
    gimbal.setPitch(pitchAngle);
}

INSTANTIATE_TEST_SUITE_P(zeroTest, GimbalPitchTest, testing::Values(std::make_tuple(0_deg, 0_deg, -10_deg, 10_deg)));
INSTANTIATE_TEST_SUITE_P(positiveTest, GimbalPitchTest, testing::Values(std::make_tuple(1_deg, 1_deg, -10_deg, 109_deg),
                                                                        std::make_tuple(10_deg, 10_deg, -10_deg, 109_deg),
                                                                        std::make_tuple(100_deg, 100_deg, -200_deg, 109_deg)));

INSTANTIATE_TEST_SUITE_P(negativeTest, GimbalPitchTest, testing::Values(std::make_tuple(-1_deg, -1_deg, -10_deg, 109_deg),
                                                                        std::make_tuple(-10_deg, -10_deg, -100_deg, 109_deg),
                                                                        std::make_tuple(-100_deg, -100_deg, -200_deg, 109_deg)));

INSTANTIATE_TEST_SUITE_P(positiveClampingTest, GimbalPitchTest, testing::Values(std::make_tuple(12_deg, 1_deg, -10_deg, 1_deg),
                                                                                std::make_tuple(103_deg, 10_deg, -10_deg, 10_deg),
                                                                                std::make_tuple(104_deg, 100_deg, -200_deg, 100_deg)));

INSTANTIATE_TEST_SUITE_P(negativeClampingTest, GimbalPitchTest, testing::Values(std::make_tuple(-12_deg, -1_deg, -1_deg, 1_deg),
                                                                                std::make_tuple(-103_deg, -10_deg, -10_deg, 10_deg),
                                                                                std::make_tuple(-150_deg, -120_deg, -120_deg, 100_deg)));

//INSTANTIATE_TEST_SUITE_P(positiveClampingTest, GimbalPitchTest, testing::Values(std::make_tuple(1_deg, 0.5_deg, -10_deg, 0.5_deg)));

//INSTANTIATE_TEST_SUITE_P(negativeTest, GimbalPitchTest, testing::Values(std::make_tuple(-1_deg, -1_deg, -10_deg, 109_deg),
//                                                                        std::make_tuple(-10_deg, -10_deg, -12_deg, 109_deg),
//                                                                        std::make_tuple(-50_deg, -50_deg, -100_deg, 109_deg)));