#include "quad_drive_subsystem.hpp"
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
        Subsystem{&drivers},
        motors_
        {
            std::move(frontLeftMotor),
            std::move(frontRightMotor),
            std::move(rearLeftMotor),
            std::move(rearRightMotor)
        }
    {
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