#include "control/turret/gimbal/field_gimbal/field_gimbal.hpp"
#include "test/mock/rail/rail_turret_mocks.hpp"

#include "units.h"

#include <gmock/gmock.h>

namespace fang::turret::fieldGimbalTest
{
    using namespace units::literals;
    // Constructs common FieldGimbal for testing with checker references
    class Setup
    {
    public:
        using PitchSystemMock = testing::NiceMock<IFieldPitchSystemMock>;
        using YawSystemMock = testing::NiceMock<IFieldYawSystemMock>;

        Setup():
            pitchSystem_{*(new PitchSystemMock{})},
            yawSystem_{*(new YawSystemMock{})},
            fieldGimbal_
            {
                drivers,
                std::unique_ptr<IFieldPitchSystem>(&pitchSystem_),
                std::unique_ptr<IFieldYawSystem>(&yawSystem_)
            }
        {
        }

        Drivers drivers{};
        PitchSystemMock& pitchSystem_;
        YawSystemMock& yawSystem_;
        FieldGimbal fieldGimbal_;
    };

    struct PitchYawParam
    {
        Radians targetPitch;
        Radians targetYaw;
    };

    class PitchYawTest:
        public Setup,
        public testing::TestWithParam<PitchYawParam>
    {
    protected:
        const Radians kTargetPitch_{GetParam().targetPitch};
        const Radians kTargetYaw_{GetParam().targetYaw};
    };

    TEST_P(PitchYawTest, pitchYawMatch)
    {
        EXPECT_CALL(pitchSystem_, setTargetFieldPitch(kTargetPitch_));
        EXPECT_CALL(yawSystem_, setTargetFieldYaw(kTargetYaw_));
        fieldGimbal_.setTargetFieldPitch(kTargetPitch_);
        fieldGimbal_.setTargetFieldYaw(kTargetYaw_);
    };

    INSTANTIATE_TEST_CASE_P
    (
        zero,
        PitchYawTest,
        testing::Values
        (
            PitchYawParam
            {
                .targetPitch = 0_deg,
                .targetYaw   = 0_deg
            }
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        positive,
        PitchYawTest,
        testing::Values
        (
            PitchYawParam
            {
                .targetPitch = 10_deg,
                .targetYaw   = 43_deg
            },
            PitchYawParam
            {
                .targetPitch = 1_deg,
                .targetYaw   = 4_deg
            },
            PitchYawParam
            {
                .targetPitch = 12_deg,
                .targetYaw   = 24_deg
            }
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        negative,
        PitchYawTest,
        testing::Values
        (
            PitchYawParam
            {
                .targetPitch = -10_deg,
                .targetYaw   = -43_deg
            },
            PitchYawParam
            {
                .targetPitch = -1_deg,
                .targetYaw   = -4_deg
            },
            PitchYawParam
            {
                .targetPitch = -12_deg,
                .targetYaw   = -24_deg
            }
        )
    );

    class InitializeUpdateTest:
        public Setup,
        public testing::Test
    {
    };

    TEST_F(InitializeUpdateTest, initialize)
    {
        EXPECT_CALL(pitchSystem_, initialize());
        EXPECT_CALL(yawSystem_, initialize());
        fieldGimbal_.initialize();
    }

    TEST_F(InitializeUpdateTest, update)
    {
        EXPECT_CALL(pitchSystem_, update());
        EXPECT_CALL(yawSystem_, update());
        fieldGimbal_.update();
    }
}