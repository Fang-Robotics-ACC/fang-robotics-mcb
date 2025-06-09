#include "control/turret/gimbal_system.hpp"

#include "unitaliases.hpp"

#include <gtest/gtest.h>
#include <tuple>

using namespace units::literals;
namespace test
{
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
        GimbalSystem::Config gimbalConfig
        {
            minPitch,
            maxPitch,
            k_defaultMotorConfig,
            k_defaultMotorConfig
        };
        const Radians setAngle{std::get<0>(GetParam())};
        const Radians expectedPitchCall{std::get<1>(GetParam())};
        const Radians minPitch{std::get<2>(GetParam())};
        const Radians maxPitch{std::get<3>(GetParam())};
        
    };
}


using namespace test;

TEST_P(GimbalPitchTest, basicPitchTest)
{
    //This tests whether or not the desired speed sent into the motor given
    //how many rounds per rotation of the feeder gear and the desired fire rate
    EXPECT_CALL(pitchMotor, setTargetPosition(expectedPitchCall));
}

INSTANTIATE_TEST_SUITE_P(zeroTest, GimbalPitchTest, testing::Values(std::make_tuple(0_deg, 0_deg, 10_deg, -10_deg)));