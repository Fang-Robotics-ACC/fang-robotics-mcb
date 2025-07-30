#include "quad_drive_subsystem.hpp"
#include "control/chassis/drive/quad_drive/data/quad_index.hpp"

namespace fang::chassis
{
    QuadDriveSubsystem::QuadDriveSubsystem
    (
        Drivers& drivers,
        std::unique_ptr<Motor> frontLeftMotor,
        std::unique_ptr<Motor> frontRightMotor,
        std::unique_ptr<Motor> rearLeftMotor,
        std::unique_ptr<Motor> rearRightMotor
    ):
        IQuadDriveSubsystem{drivers},
        motors_
        {
            std::move(frontLeftMotor),
            std::move(frontRightMotor),
            std::move(rearLeftMotor),
            std::move(rearRightMotor)
        }
    {
    }

    void QuadDriveSubsystem::setTargetWheelSpeeds(const QuadRPM& wheelSpeeds)
    {
        motors_[QuadIndex::kFrontLeft]->setTargetSpeed(wheelSpeeds.frontLeft);
        motors_[QuadIndex::kfrontRight]->setTargetSpeed(wheelSpeeds.frontRight);
        motors_[QuadIndex::kRearLeft]->setTargetSpeed(wheelSpeeds.rearLeft);
        motors_[QuadIndex::kRearRight]->setTargetSpeed(wheelSpeeds.rearRight);
    }

    void QuadDriveSubsystem::initialize()
    {
        for(std::unique_ptr<Motor>& motor: motors_)
        {
            motor->initialize();
        }
    }

    void QuadDriveSubsystem::refresh()
    {
        for(std::unique_ptr<Motor>& motor: motors_)
        {
            motor->update();
        }
    }
}