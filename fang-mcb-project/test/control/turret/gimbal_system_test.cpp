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
        PositionMotor& yawMotor{gimbalSystem.m_pitchMotor};

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

    class GimbalPitchTest: public GimbalSystemTest, public ::testing::TestWithParam<std::tuple<Radians, Radians, Radians, Radians>>
    {
    public:
        GimbalPitchTest() : GimbalSystemTest(gimbalConfig){}
        
        const Radians pitchAngle{std::get<0>(GetParam())};
        const Radians expectedPitchCall{std::get<1>(GetParam())};
        const Radians minPitch{std::get<2>(GetParam())};
        const Radians maxPitch{std::get<3>(GetParam())};
        GimbalSystem::Config gimbalConfig
        {
            minPitch,
            maxPitch,
            k_defaultMotorConfig,
            k_defaultMotorConfig
        };
    };
}


using namespace test;

TEST_P(GimbalPitchTest, basicPitchTest)
{
    //This tests the pitch clamping functionality
    EXPECT_CALL(pitchMotor, setTargetPosition((expectedPitchCall, testing::UnitEq(expectedPitchCall))));
    gimbalSystem.setPitch(pitchAngle);
}

INSTANTIATE_TEST_SUITE_P(zeroTest, GimbalPitchTest, testing::Values(std::make_tuple(0_deg, 0_deg, -10_deg, 10_deg)));
INSTANTIATE_TEST_SUITE_P(positiveTest, GimbalPitchTest, testing::Values(std::make_tuple(1_deg, 1_deg, -10_deg, 109_deg),
                                                                        std::make_tuple(10_deg, 10_deg, -10_deg, 109_deg),
                                                                        std::make_tuple(100_deg, 100_deg, -200_deg, 109_deg)));

INSTANTIATE_TEST_SUITE_P(negativeTest, GimbalPitchTest, testing::Values(std::make_tuple(-1_deg, -1_deg, -10_deg, 109_deg),
                                                                        std::make_tuple(-10_deg, -10_deg, -100_deg, 109_deg),
                                                                        std::make_tuple(-100_deg, -100_deg, -200_deg, 109_deg)));

//INSTANTIATE_TEST_SUITE_P(negativeTest, GimbalPitchTest, testing::Values(std::make_tuple(-1_deg, -1_deg, -10_deg, 109_deg),
//                                                                        std::make_tuple(-10_deg, -10_deg, -12_deg, 109_deg),
//                                                                        std::make_tuple(-50_deg, -50_deg, -100_deg, 109_deg)));