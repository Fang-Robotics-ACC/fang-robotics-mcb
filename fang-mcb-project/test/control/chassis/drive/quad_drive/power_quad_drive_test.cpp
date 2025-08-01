#include "control/chassis/drive/quad_drive/power_quad_drive/power_quad_drive.hpp"
#include "test/mock/rail/rail_motor_mocks.hpp"
#include "rail/mock/chassis/ipower_limiter_system_mock.hpp"
#include "driver/drivers.hpp"

#include <memory>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace fang::chassis
{
    using namespace units::literals;
    /**
     * Create a subsystem as well as reference
     * accessors for checking calls to motors
     */
    class PowerQuadDriveTestSetup 
    {
    public:
        using ISpeedMotorMock = testing::NiceMock<motor::ISpeedMotorMock>;
        using IPowerLimiterSystemMock = testing::NiceMock<rail::chassis::IPowerLimiterSystemMock>;
        using Motors = PowerQuadDrive::Motors;
        PowerQuadDriveTestSetup():
            //Only used for tests, this prevents duplication
            frontLeftMotor_{*(new ISpeedMotorMock{})},
            frontRightMotor_{*(new ISpeedMotorMock{})},
            rearLeftMotor_{*(new ISpeedMotorMock{})},
            rearRightMotor_{*(new ISpeedMotorMock{})},
            powerLimiter_{*(new IPowerLimiterSystemMock{})},
            quadDrive_ 
            {
                drivers_,
                Motors
                {
                    std::unique_ptr<motor::ISpeedMotor>(&frontLeftMotor_),
                    std::unique_ptr<motor::ISpeedMotor>(&frontRightMotor_),
                    std::unique_ptr<motor::ISpeedMotor>(&rearLeftMotor_),
                    std::unique_ptr<motor::ISpeedMotor>(&rearRightMotor_)
                },
                std::unique_ptr<rail::chassis::IPowerLimiterSystem>(&powerLimiter_)
            }
        {
        }
    private:
        //Prevents dangling references
        //Since these pointers are invalid they should not be accessible to the client
    protected:
        motor::ISpeedMotorMock& frontLeftMotor_;
        motor::ISpeedMotorMock& frontRightMotor_;
        motor::ISpeedMotorMock& rearLeftMotor_;
        motor::ISpeedMotorMock& rearRightMotor_;
        IPowerLimiterSystemMock& powerLimiter_;
        PowerQuadDrive quadDrive_;

        Drivers drivers_{};
    };

    class PowerQuadDriveTest:
        public PowerQuadDriveTestSetup,
        public ::testing::Test
    {
    };

    struct WheelSpeedSetterParam
    {
        QuadRPM targetWheelSpeeds;
        double limitRatio;
    };
    class WheelSpeedSetter:
        virtual public PowerQuadDriveTestSetup,
        virtual public ::testing::TestWithParam<WheelSpeedSetterParam>
    {
    protected:
        WheelSpeedSetterParam param{GetParam()};
        QuadRPM targetWheelSpeeds_{param.targetWheelSpeeds};
        double limitRatio_{param.limitRatio};
    };


    /**
     * The motor speeds should be scaled in accordance to the
     * limit ratio
     */
    TEST_P(WheelSpeedSetter, motorSpeedScaling)
    {
        QuadRPM scaledWheelSpeeds{targetWheelSpeeds_ * limitRatio_};
        //Make sure the right wheel speeds are set
        EXPECT_CALL(frontLeftMotor_, setTargetSpeed(scaledWheelSpeeds.frontLeft));
        EXPECT_CALL(frontRightMotor_, setTargetSpeed(scaledWheelSpeeds.frontRight));
        EXPECT_CALL(rearLeftMotor_, setTargetSpeed(scaledWheelSpeeds.rearLeft));
        EXPECT_CALL(rearRightMotor_, setTargetSpeed(scaledWheelSpeeds.rearRight));

        quadDrive_.setTargetWheelSpeeds(targetWheelSpeeds_);
    }

    INSTANTIATE_TEST_CASE_P
    (
        zero,
        WheelSpeedSetter,
        ::testing::Values
        (
            WheelSpeedSetterParam{{0_rpm, 0_rpm, 0_rpm, 0_rpm}, 1.0}
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        positiveOnly,
        WheelSpeedSetter,
        ::testing::Values
        (
            WheelSpeedSetterParam{{20_rpm, 40_rpm, 80_rpm, 120_rpm}, 0.5},
            WheelSpeedSetterParam{{0.5_rpm, 1_rpm, 2_rpm, 4_rpm}, 0.2}
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        negativeOnly,
        WheelSpeedSetter,
        ::testing::Values
        (
            WheelSpeedSetterParam{{-12_rpm, -234_rpm, -345345.2_rpm, -435_rpm}, 0.2},
            WheelSpeedSetterParam{{-1_rpm, -1_rpm, -2_rpm, -4_rpm}, 0.1}
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        mixed,
        WheelSpeedSetter,
        ::testing::Values
        (
            WheelSpeedSetterParam{{-12.345345_rpm, 234_rpm, -345345.2_rpm, 435.345_rpm}, 0.1},
            WheelSpeedSetterParam{{-1_rpm, -345345_rpm, 2_rpm, -4_rpm}, 0.3}
        )
    );

    //All motors should be initialized and updated on
    TEST_F(PowerQuadDriveTest, initialize)
    {
        EXPECT_CALL(frontLeftMotor_, initialize);
        EXPECT_CALL(frontRightMotor_, initialize);
        EXPECT_CALL(rearLeftMotor_, initialize);
        EXPECT_CALL(rearRightMotor_, initialize);
        quadDrive_.initialize();
    }

    //All motors should be initialized and updated on
    TEST_F(PowerQuadDriveTest, update)
    {
        EXPECT_CALL(frontLeftMotor_, update);
        EXPECT_CALL(frontRightMotor_, update);
        EXPECT_CALL(rearLeftMotor_, update);
        EXPECT_CALL(rearRightMotor_, update);
        quadDrive_.refresh();
    }
}