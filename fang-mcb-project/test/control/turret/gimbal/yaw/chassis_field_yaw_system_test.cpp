#include "control/turret/gimbal/yaw/chassis_field_yaw_system/chassis_field_yaw_system.hpp"
#include "test/mock/trap/communication/sensors/iimu_mock.hpp"
#include "test/mock/rail/rail_motor_mocks.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace fang::turret
{
    using namespace units::literals;
    class FieldYawTestSetup
    {
    public:
        using Motor = ChassisFieldYawSystem::Motor;
        using Imu  = ChassisFieldYawSystem::Imu;
        using ImuMock = testing::NiceMock<trap::communication::sensors::IImuMock>;
        using MotorMock = testing::NiceMock<motor::IPositionMotorMock>;
        using Config = ChassisFieldYawSystem::Config;

        FieldYawTestSetup(const Config& config):
            motor_{*(new MotorMock{})},
            imu_{*(new ImuMock{})},
            yawSystem_
            {
                std::unique_ptr<Motor>(&motor_),
                std::unique_ptr<Imu>(&imu_),
                config
            }
        {
        }
    protected: 

    MotorMock& motor_;
    ImuMock& imu_;
    ChassisFieldYawSystem yawSystem_;
    };

    struct TargetFieldYawParam
    {
        Radians targetFieldYaw;
        Radians chassisAngle;
        Radians expectedMotorAngle;
    };

    /**
     * Check if the system properly compensates for the chassis input
     */
    class TargetFieldYawTest:
        public FieldYawTestSetup,
        public ::testing::TestWithParam<TargetFieldYawParam>
    {
    public:
        TargetFieldYawTest():
            FieldYawTestSetup({0_rad}) //Test the field yaw independent from yaw error
        {}
    protected:
        const TargetFieldYawParam param{GetParam()};
        Radians targetFieldYaw_{param.targetFieldYaw};
        Radians chassisAngle_{param.chassisAngle};
        Radians expectedAngle_{param.expectedMotorAngle};
    };

    
    TEST_P(TargetFieldYawTest, targetFieldYaw)
    {
        ON_CALL(imu_, getYaw()).WillByDefault(testing::Return(chassisAngle_));
        EXPECT_CALL(motor_, setTargetPosition(expectedAngle_));
        yawSystem_.setTargetFieldYaw(targetFieldYaw_);
    }

    INSTANTIATE_TEST_CASE_P
    (
        zero,
        TargetFieldYawTest,
        testing::Values
        (
            TargetFieldYawParam
            {
                .targetFieldYaw     = 0_rad,
                .chassisAngle       = 0_rad,
                .expectedMotorAngle = 0_rad,
            }
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        positive,
        TargetFieldYawTest,
        testing::Values
        (
            TargetFieldYawParam
            {
                .targetFieldYaw     = 15_rad,
                .chassisAngle       = 15_rad,
                .expectedMotorAngle = 0_rad
            },
            TargetFieldYawParam
            {
                .targetFieldYaw     = 30_rad,
                .chassisAngle       = 15_rad,
                .expectedMotorAngle = 15_rad
            }
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        negative,
        TargetFieldYawTest,
        testing::Values
        (
            TargetFieldYawParam
            {
                .targetFieldYaw     = -15_rad,
                .chassisAngle       =  15_rad,
                .expectedMotorAngle = -30_rad
            },
            TargetFieldYawParam
            {
                .targetFieldYaw     = -30_rad,
                .chassisAngle       =  30_rad,
                .expectedMotorAngle = -60_rad
            }
        )
    );

    struct YawErrorCorrectionParam
    {
        Radians targetFieldYaw;
        ChassisFieldYawSystem::Config config; //Yaw error correction
    };

    /**
     * Tests if the zero position compensates for a zero position on the
     * motor which is offset from the chassis zero position.
     * (e.g. the turret faces to the left of the robot)
     */
    class YawErrorCorrectionTest:
        public FieldYawTestSetup,
        public ::testing::TestWithParam<YawErrorCorrectionParam>
    {
    public:
        YawErrorCorrectionTest():
            FieldYawTestSetup(param.config)
        {}
    protected:
        const YawErrorCorrectionParam param{GetParam()};
        Radians targetFieldYaw_{param.targetFieldYaw};
    };

}