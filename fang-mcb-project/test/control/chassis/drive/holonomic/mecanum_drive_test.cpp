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
        MecanumDriveTestMockup():
            quadDrive_{*(new fang::chassis::IQuadDriveMock())},
            imu_{*(new trap::communication::sensors::IImuMock{})},
            mecanumDrive_
            {
                drivers_,
                std::unique_ptr<IQuadDrive>(&quadDrive_),
                std::unique_ptr<Imu>(&imu_),
                kDefaultConfig
            }
        {
        }
    private:
        std::unique_ptr<IQuadDrive>quadDrivePtr_;
        std::unique_ptr<Imu>imuPtr_;
    protected:
        Drivers drivers_{};
        IQuadDrive& quadDrive_;
        Imu& imu_;

        MecanumDrive mecanumDrive_;

    };

}