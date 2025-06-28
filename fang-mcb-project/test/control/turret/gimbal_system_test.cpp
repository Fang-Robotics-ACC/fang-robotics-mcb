#include "gimbal_system_test_archetypes.hpp"
#include "control/turret/systems/gimbal_system.hpp"

#include "unitaliases.hpp"

#include <gtest/gtest.h>
#include <tuple>
#include "test/unit_matcher.h"

using namespace units::literals;



using namespace test;
using namespace testing;

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

TEST_P(GimbalYawTest, basicPitchTest)
{
    const GimbalSystemTest::GimbalSystem::Config gimbalConfig
    {
        //Allow full range
        -360_deg,
        360_deg,
        GimbalSystemTest::k_defaultMotorConfig,
        GimbalSystemTest::k_defaultMotorConfig
    };

    GimbalSystemTest test{gimbalConfig};
    GimbalSystemTest::GimbalSystem& gimbal{test.gimbalSystem};

    //This tests the pitch clamping functionality
    EXPECT_CALL(test.yawMotor, setTargetPosition((yawAngle, testing::UnitEq(yawAngle))));
    gimbal.setYaw(yawAngle);
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

INSTANTIATE_TEST_SUITE_P(zeroTest, GimbalYawTest, testing::Values(std::make_tuple(0_deg)));
INSTANTIATE_TEST_SUITE_P(positiveTest, GimbalYawTest, testing::Values(std::make_tuple(103_deg)));
INSTANTIATE_TEST_SUITE_P(negativeTest, GimbalYawTest, testing::Values(std::make_tuple(-10_deg)));

TEST(updateTest, GimbalSystem)
{
    //Make sure that all associated motors are updated
    const GimbalSystemTest::GimbalSystem::Config gimbalConfig
    {
        //Allow full range
        -360_deg,
        360_deg,
        GimbalSystemTest::k_defaultMotorConfig,
        GimbalSystemTest::k_defaultMotorConfig
    };

    GimbalSystemTest test{gimbalConfig};
    EXPECT_CALL(test.yawMotor, update());
    EXPECT_CALL(test.pitchMotor, update());
    test.gimbalSystem.update();
}

TEST_P(GimbalAddPitchTest, basicPitchTest)
{
    const GimbalSystemTest::GimbalSystem::Config gimbalConfig
    {
        //Allow full range
        -360_deg,
        360_deg,
        GimbalSystemTest::k_defaultMotorConfig,
        GimbalSystemTest::k_defaultMotorConfig
    };

    GimbalSystemTest test{gimbalConfig};
    GimbalSystemTest::GimbalSystem& gimbal{test.gimbalSystem};

    //This tests the pitch clamping functionality
    ON_CALL(test.pitchMotor, getPosition()).WillByDefault(Return(startAngle));
    EXPECT_CALL(test.pitchMotor, setTargetPosition((expectedAngle, testing::UnitEq(expectedAngle))));
    gimbal.addPitch(addAngle);
}

INSTANTIATE_TEST_SUITE_P(positiveTest, GimbalAddPitchTest, testing::Values(std::make_tuple(1_deg, 10_deg, 11_deg),
                                                                           std::make_tuple(10_deg, 10_deg, 20_deg),
                                                                           std::make_tuple(100_deg, 200_deg, 300_deg)));

INSTANTIATE_TEST_SUITE_P(negativeTest, GimbalAddPitchTest, testing::Values(std::make_tuple(1_deg, -10_deg, -9_deg),
                                                                           std::make_tuple(10_deg, -10_deg, 0_deg),
                                                                           std::make_tuple(100_deg, -200_deg, -100_deg)));

TEST_P(GimbalAddYawTest, basicAddYawTest)
{
    const GimbalSystemTest::GimbalSystem::Config gimbalConfig
    {
        //Allow full range
        -360_deg,
        360_deg,
        GimbalSystemTest::k_defaultMotorConfig,
        GimbalSystemTest::k_defaultMotorConfig
    };

    GimbalSystemTest test{gimbalConfig};
    GimbalSystemTest::GimbalSystem& gimbal{test.gimbalSystem};

    //This tests the pitch clamping functionality
    ON_CALL(test.yawMotor, getPosition()).WillByDefault(Return(startAngle));
    EXPECT_CALL(test.yawMotor, setTargetPosition((expectedAngle, testing::UnitEq(expectedAngle))));
    gimbal.addYaw(addAngle);
}

INSTANTIATE_TEST_SUITE_P(positiveTest, GimbalAddYawTest, testing::Values(std::make_tuple(1_deg, 10_deg, 11_deg),
                                                                           std::make_tuple(10_deg, 10_deg, 20_deg),
                                                                           std::make_tuple(100_deg, 200_deg, 300_deg)));

INSTANTIATE_TEST_SUITE_P(negativeTest, GimbalAddYawTest, testing::Values(std::make_tuple(1_deg, -10_deg, -9_deg),
                                                                           std::make_tuple(10_deg, -10_deg, 0_deg),
                                                                           std::make_tuple(100_deg, -200_deg, -100_deg)));

