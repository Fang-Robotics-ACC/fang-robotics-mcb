#include "control/turret/gimbal_system.hpp"

#include "unitaliases.hpp"

#include <gtest/gtest.h>
#include <tuple>

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
        GimbalPitchTest() 
        :   pitchAngle{std::get<0>(GetParam())},
            expectedPitchCall{std::get<1>(GetParam())},
            minPitch{std::get<2>(GetParam())},
            maxPitch{std::get<3>(GetParam())},
            gimbalConfig
            {
                minPitch,
                maxPitch,
                k_defaultMotorConfig,
                k_defaultMotorConfig
            },
            GimbalSystemTest(gimbalConfig){}

        const Radians pitchAngle;
        const Radians expectedPitchCall;
        const Radians minPitch;
        const Radians maxPitch;
        const GimbalSystem::Config gimbalConfig;
        
    };
}


using namespace test;

TEST_P(GimbalPitchTest, basicPitchTest)
{
    //This tests the pitch clamping functionality
    EXPECT_CALL(pitchMotor, setTargetPosition(expectedPitchCall));
    gimbalSystem.setPitch(pitchAngle);
}

INSTANTIATE_TEST_SUITE_P(zeroTest, GimbalPitchTest, testing::Values(std::make_tuple(0_deg, 0_deg, -10_deg, 10_deg)));
INSTANTIATE_TEST_SUITE_P(positiveTest, GimbalPitchTest, testing::Values(std::make_tuple(1_deg, 1_deg, -10_deg, 109_deg)));