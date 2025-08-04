#include "control/turret/gimbal/pitch/basic_field_pitch_system/basic_field_pitch_system.hpp"
#include "test/mock/trap/communication/sensors/iimu_mock.hpp"
#include "test/mock/rail/rail_motor_mocks.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace fang::turret
{
    using namespace units::literals;
    class FieldPitchTestSetup
    {
    public:
        using Motor = BasicFieldPitchSystem::Motor;
        using Imu  = BasicFieldPitchSystem::Imu;
        using MotorMock = testing::NiceMock<motor::IPositionMotorMock>;
        using Config = BasicFieldPitchSystem::Config;

        FieldPitchTestSetup(const Config& config):
            motor_{*(new MotorMock{})},
            pitchSystem_
            {
                std::unique_ptr<Motor>(&motor_),
                config
            }
        {
        }

    MotorMock& motor_;
    BasicFieldPitchSystem pitchSystem_;
    };

    struct PitchClampParam
    {
        Radians targetFieldPitch;
        Radians expectedMotorAngle;
        BasicFieldPitchSystem::PitchRange pitchRange;
    };

    /**
     * Tests if the zero position compensates for a zero position on the
     * motor which is offset from the chassis zero position.
     * (e.g. the turret faces to the left of the robot)
     */
    class PitchClampTest : public ::testing::TestWithParam<PitchClampParam>
    {
    public:
        PitchClampTest(){}
    protected:
        const PitchClampParam param{GetParam()};
        // Due to order of initialization and the need
        // to pass the config variable, this semi-hack is done
        FieldPitchTestSetup test
        {
            BasicFieldPitchSystem::Config
            {
                .pitchError = 0_rad,
                .pitchRange = param.pitchRange
            }
        };
        const Radians expectedMotorAngle_{param.expectedMotorAngle};
        const Radians targetFieldPitch_{param.targetFieldPitch};
    };

    TEST_P(PitchClampTest, yawErrorCorrectionTest)
    {
        //Make the test independent of chassis error correction
        EXPECT_CALL(test.motor_, setTargetPosition(expectedMotorAngle_));
        test.pitchSystem_.setTargetFieldPitch(targetFieldPitch_);
    }

    INSTANTIATE_TEST_CASE_P
    (
        zero,
        PitchClampTest,
        testing::Values
        (
            PitchClampParam
            {
                .targetFieldPitch   = 0_deg,
                .expectedMotorAngle = 0_deg,
                .pitchRange         = {-10_deg, 10_deg}
            }
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        positiveAndClamp,
        PitchClampTest,
        testing::Values
        (
            PitchClampParam
            {
                .targetFieldPitch   = 9_deg,
                .expectedMotorAngle = 9_deg,
                .pitchRange         = {-10_deg, 10_deg}
            },
            PitchClampParam
            {
                .targetFieldPitch   = 100_deg,
                .expectedMotorAngle = 10_deg, // Should be clamped
                .pitchRange         = {-10_deg, 10_deg}
            }
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        negativeAndClamp,
        PitchClampTest,
        testing::Values
        (
            PitchClampParam
            {
                .targetFieldPitch   = -9_deg,
                .expectedMotorAngle = -9_deg,
                .pitchRange         = {-10_deg, 10_deg}
            },
            PitchClampParam
            {
                .targetFieldPitch   = -100_deg,
                .expectedMotorAngle = -10_deg, // Should be clamped
                .pitchRange         = {-10_deg, 10_deg}
            }
        )
    );
}