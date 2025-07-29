#include "control/chassis/drive/quad_drive/quad_drive_subsystem/quad_drive_subsystem.hpp"
#include "test/mock/rail/rail_motor_mocks.hpp"
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
    class QuadDriveSubsystemTestSetup
    {
    public:
        QuadDriveSubsystemTestSetup():
            frontLeftMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},
            frontRightMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},
            rearLeftMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},
            rearRightMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},

            //This is needed to gain access into the motor states, only required for testing
            //Otherwise the motor states are inaccessible (unique pointer stuff)
            frontLeftMotor_{*frontLeftMotorPtr_},
            frontRightMotor_{*frontRightMotorPtr_},
            rearLeftMotor_{*rearLeftMotorPtr_},
            rearRightMotor_{*rearRightMotorPtr_},

            quadDriveSubsystem_
            {
                drivers_,
                std::move(frontLeftMotorPtr_),
                std::move(frontRightMotorPtr_),
                std::move(rearLeftMotorPtr_),
                std::move(rearRightMotorPtr_)
            }
        {
        }
    private:
        //Prevents dangling references
        //Since these pointers are invalid they should not be accessible to the client
        std::unique_ptr<motor::ISpeedMotorMock> frontLeftMotorPtr_;
        std::unique_ptr<motor::ISpeedMotorMock> frontRightMotorPtr_;
        std::unique_ptr<motor::ISpeedMotorMock> rearLeftMotorPtr_;
        std::unique_ptr<motor::ISpeedMotorMock> rearRightMotorPtr_;
    protected:
        motor::ISpeedMotorMock& frontLeftMotor_;
        motor::ISpeedMotorMock& frontRightMotor_;
        motor::ISpeedMotorMock& rearLeftMotor_;
        motor::ISpeedMotorMock& rearRightMotor_;
        QuadDriveSubsystem quadDriveSubsystem_;

        Drivers drivers_{};
    };

    class QuadDriveSubsystemTest:
        public QuadDriveSubsystemTestSetup,
        public ::testing::Test
    {
    };

    struct WheelSpeedSetterParam
    {
        QuadRPM targetWheelSpeeds;
    };
    class WheelSpeedSetter:
        virtual public QuadDriveSubsystemTestSetup,
        virtual public ::testing::TestWithParam<WheelSpeedSetterParam>
    {
    protected:
        WheelSpeedSetterParam param{GetParam()};
        QuadRPM targetWheelSpeeds_{param.targetWheelSpeeds};
    };

    TEST_P(WheelSpeedSetter, setMotorSpeeds)
    {
        //Make sure the right wheel speeds are set
        EXPECT_CALL(frontLeftMotor_, setTargetSpeed(targetWheelSpeeds_.frontLeft));
        EXPECT_CALL(frontRightMotor_, setTargetSpeed(targetWheelSpeeds_.frontRight));
        EXPECT_CALL(rearLeftMotor_, setTargetSpeed(targetWheelSpeeds_.rearLeft));
        EXPECT_CALL(rearRightMotor_, setTargetSpeed(targetWheelSpeeds_.rearRight));
        quadDriveSubsystem_.setTargetWheelSpeeds(targetWheelSpeeds_);
    }

    INSTANTIATE_TEST_CASE_P
    (
        zero,
        WheelSpeedSetter,
        ::testing::Values
        (
            WheelSpeedSetterParam{{0_rpm, 0_rpm, 0_rpm, 0_rpm}}
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        positiveOnly,
        WheelSpeedSetter,
        ::testing::Values
        (
            WheelSpeedSetterParam{{12_rpm, 234_rpm, 345345.2_rpm, 435_rpm}},
            WheelSpeedSetterParam{{1_rpm, 1_rpm, 2_rpm, 4_rpm}}
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        negativeOnly,
        WheelSpeedSetter,
        ::testing::Values
        (
            WheelSpeedSetterParam{{-12_rpm, -234_rpm, -345345.2_rpm, -435_rpm}},
            WheelSpeedSetterParam{{-1_rpm, -1_rpm, -2_rpm, -4_rpm}}
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        mixed,
        WheelSpeedSetter,
        ::testing::Values
        (
            WheelSpeedSetterParam{{-12.345345_rpm, 234_rpm, -345345.2_rpm, 435.345_rpm}},
            WheelSpeedSetterParam{{-1_rpm, -345345_rpm, 2_rpm, -4_rpm}}
        )
    );

    //All motors should be initialized and updated on
    TEST_F(QuadDriveSubsystemTest, initialize)
    {
        EXPECT_CALL(frontLeftMotor_, initialize);
        EXPECT_CALL(frontRightMotor_, initialize);
        EXPECT_CALL(rearLeftMotor_, initialize);
        EXPECT_CALL(rearRightMotor_, initialize);
        quadDriveSubsystem_.initialize();
    }

    //All motors should be initialized and updated on
    TEST_F(QuadDriveSubsystemTest, update)
    {
        EXPECT_CALL(frontLeftMotor_, update);
        EXPECT_CALL(frontRightMotor_, update);
        EXPECT_CALL(rearLeftMotor_, update);
        EXPECT_CALL(rearRightMotor_, update);
        quadDriveSubsystem_.initialize();
    }
}