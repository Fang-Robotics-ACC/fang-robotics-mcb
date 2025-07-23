#ifndef FANG_ROBOTICS_MCB_GIMBAL_SYSTEM_TEST_ARCHETYPES_HPP
#define FANG_ROBOTICS_MCB_GIMBAL_SYSTEM_TEST_ARCHETYPES_HPP
#include "control/turret/system/gimbal_system.hpp"
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

    class GimbalYawTest: public ::testing::TestWithParam<std::tuple<Radians>>
    {
    public:
        const Radians yawAngle{std::get<0>(GetParam())};
    };

    class GimbalAddPitchTest: public ::testing::TestWithParam<std::tuple<Radians, Radians, Radians>>
    {
    public:
        const Radians startAngle{std::get<0>(GetParam())};
        const Radians addAngle{std::get<1>(GetParam())};
        const Radians expectedAngle{std::get<2>(GetParam())};
    };

    class GimbalAddYawTest : public ::testing::TestWithParam<std::tuple<Radians, Radians, Radians>>
    {
    public:
        const Radians startAngle{std::get<0>(GetParam())};
        const Radians addAngle{std::get<1>(GetParam())};
        const Radians expectedAngle{std::get<2>(GetParam())};
    };
}
#endif