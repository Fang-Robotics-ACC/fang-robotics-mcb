#include "control/turret/gimbal/yaw/chassis_field_yaw_system/chassis_field_yaw_system.hpp"
#include "test/mock/trap/communication/sensors/iimu_mock.hpp"
#include "test/mock/rail/rail_motor_mocks.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace fang::turret
{
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
}