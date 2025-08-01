#include "control/chassis/drive/holonomic/mecanum/mecanum_drive/mecanum_drive.hpp"

#include "test/mock/rail/rail_chassis_mocks.hpp"
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
    private:
        std::unique_ptr<IQuadDriveMock>quadDrivePtr_;
        std::unique_ptr<ImuMock>imuPtr_;
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

    TEST_F(MecanumDriveSystemTest, initialize)
    {
        EXPECT_CALL(quadDrive_, initialize());
        mecanumDrive_.initialize();
    }
}