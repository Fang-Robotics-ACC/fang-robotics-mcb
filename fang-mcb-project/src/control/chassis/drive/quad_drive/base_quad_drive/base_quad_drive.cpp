#include "base_quad_drive.hpp"
#include "control/chassis/drive/quad_drive/data/quad_index.hpp"

namespace fang::chassis
{
    BaseQuadDrive::BaseQuadDrive
    (
        Drivers& drivers,
        std::unique_ptr<Motor> frontLeftMotor,
        std::unique_ptr<Motor> frontRightMotor,
        std::unique_ptr<Motor> rearLeftMotor,
        std::unique_ptr<Motor> rearRightMotor
    ):
        QuadDriveSubsystem{drivers},
        motors_
        {
            std::move(frontLeftMotor),
            std::move(frontRightMotor),
            std::move(rearLeftMotor),
            std::move(rearRightMotor)
        }
    {
    }

    void BaseQuadDrive::setTargetWheelSpeeds(const QuadRPM& wheelSpeeds)
    {
        motors_[QuadIndex::kFrontLeft]->setTargetSpeed(wheelSpeeds.frontLeft);
        motors_[QuadIndex::kfrontRight]->setTargetSpeed(wheelSpeeds.frontRight);
        motors_[QuadIndex::kRearLeft]->setTargetSpeed(wheelSpeeds.rearLeft);
        motors_[QuadIndex::kRearRight]->setTargetSpeed(wheelSpeeds.rearRight);
    }

    void BaseQuadDrive::initialize()
    {
        for(std::unique_ptr<Motor>& motor: motors_)
        {
            motor->initialize();
        }
    }

    void BaseQuadDrive::update()
    {
        for(std::unique_ptr<Motor>& motor: motors_)
        {
            motor->update();
        }
    }
    void BaseQuadDrive::refresh()
    {
        update();
    }

}