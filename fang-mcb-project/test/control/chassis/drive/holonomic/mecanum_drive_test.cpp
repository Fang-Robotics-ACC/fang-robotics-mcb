#include "control/chassis/drive/holonomic/mecanum/mecanum_drive/mecanum_drive.hpp"

#include "test/mock/rail/rail_chassis_mocks.hpp"
#include "test/wrap/rail/chassis/quad_drive_match.hpp"
#include "test/mock/trap/communication/sensors/iimu_mock.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace fang::chassis
{
    using namespace units::literals;
    constexpr FieldMecanumLogic::Config kDefaultMecanumLogicConfig
    {
        .horizontalWheelDistance = 1_m,
        .verticalWheelDistance = 1_m,
        .wheelRadius = 0.5_m
    };

    constexpr MecanumDrive::Config kDefaultConfig
    {
        .mecanumLogicConfig =  kDefaultMecanumLogicConfig
    };
    /**
     * Create a subsystem as well as reference
     * accessors for checking calls to motors
     */
    class MecanumDriveTestMockup
    {
    protected:
        using Imu = MecanumDrive::Imu;
        using ImuMock = trap::communication::sensors::IImuMock;
        MecanumDriveTestMockup():
            //These will become smart pointers, so no worries
            quadDrive_{*(new IQuadDriveMock{})},
            imu_{*(new ImuMock{})},
            mecanumDrive_
            {
                drivers_,
                std::unique_ptr<IQuadDrive>{&quadDrive_},
                std::unique_ptr<MecanumDrive::Imu>{&imu_},
                kDefaultConfig
            }
        {
        }
    protected:
        Drivers drivers_{};
        IQuadDriveMock& quadDrive_;
        ImuMock& imu_;
        MecanumDrive mecanumDrive_;
    };

    class MecanumDriveSystemTest:
        public MecanumDriveTestMockup,
        public ::testing::Test
    {
    };

    //The MecanumDrive manages a quadDrive which must be initialized and updated
    //As it is delegating some functionality to the mecanum drive, it is being tested
    //for it actually being called :D

    TEST_F(MecanumDriveSystemTest, initialize)
    {
        EXPECT_CALL(quadDrive_, initialize());
        mecanumDrive_.initialize();
    }

    TEST_F(MecanumDriveSystemTest, updateAndRefresh)
    {
        EXPECT_CALL(quadDrive_, update());
        mecanumDrive_.refresh();
        EXPECT_CALL(quadDrive_, update());
        mecanumDrive_.update();
    }

    struct LogicSyncTestParam
    {
        Velocity2D targetTranslation;
        RPM targetRotation;
        Radians fieldAngle;
        FieldMecanumLogic::Config mecanumLogicConfig;
    };

    class MecanumDriveMecanumLogicSync:
        public MecanumDriveTestMockup,
        public ::testing::TestWithParam<LogicSyncTestParam>
    {
    protected:
        const LogicSyncTestParam param{GetParam()};
        const Velocity2D targetTranslation_{param.targetTranslation};
        const RPM targetRotation_{param.targetRotation};
        const Radians fieldAngle_{param.fieldAngle};
        const FieldMecanumLogic::Config mecanumLogicConfig_{param.mecanumLogicConfig};
    };

    /*
     * /*The correct wheel speeds must be syncrhonized
     * mecanum logic does not have any variations, it is a
     * specific mathematical operation.
     *
     * This checks that the quadDrive_ is being passed
     * the wheel speeds as well as the correct ones
     * during the refresh.
     *
     * Since the mecanum logic is reliant on the imu to provide information,
     * this checks the imu syncrhonization as well
     */
    TEST_P(MecanumDriveMecanumLogicSync, mecanumImusync)
    {
        FieldMecanumLogic fieldLogic{mecanumLogicConfig_};
        ON_CALL(imu_, getYaw()).WillByDefault(testing::Return(fieldAngle_));
        fieldLogic.setRobotAngle(fieldAngle_);

        fieldLogic.setTranslation(targetTranslation_);
        fieldLogic.setRotation(targetRotation_);

        mecanumDrive_.setTargetTranslation(targetTranslation_);
        mecanumDrive_.setTargetRotation(targetRotation_);

        QuadRPM expectedWheelSpeeds{fieldLogic.getWheelSpeeds()};
        EXPECT_CALL(quadDrive_, setTargetWheelSpeeds(quadDriveDataEq(expectedWheelSpeeds)));
        mecanumDrive_.update();
    }

    INSTANTIATE_TEST_CASE_P
    (
        zeroTest, MecanumDriveMecanumLogicSync,
        ::testing::Values
        (
            LogicSyncTestParam
            {
                .targetTranslation = {0_mps, 0_mps},
                .targetRotation = 0_rpm,
                .fieldAngle = 0_rad,
                .mecanumLogicConfig = kDefaultMecanumLogicConfig
            }
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        mixedTest, MecanumDriveMecanumLogicSync,
        ::testing::Values
        (
            LogicSyncTestParam
            {
                .targetTranslation = {100234_mps, -345_mps},
                .targetRotation = -345_rpm,
                .fieldAngle = 345_rad,
                .mecanumLogicConfig = kDefaultMecanumLogicConfig
            },
            LogicSyncTestParam
            {
                .targetTranslation = {-1034.345_mps, 345.345345_mps},
                .targetRotation = -2_rpm,
                .fieldAngle = -23_rad,
                .mecanumLogicConfig = kDefaultMecanumLogicConfig
            },
            LogicSyncTestParam
            {
                .targetTranslation = {-1034534.345_mps, 45349585.345345_mps},
                .targetRotation = -234545_rpm,
                .fieldAngle = 234_rad,
                .mecanumLogicConfig = kDefaultMecanumLogicConfig
            }
        )
    );
}