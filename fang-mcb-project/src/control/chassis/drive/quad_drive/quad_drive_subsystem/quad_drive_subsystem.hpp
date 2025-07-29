#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_QUAD_SUBSYSTEM_DRIVE_QUAD_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_QUAD_SUBSYSTEM_DRIVE_QUAD_SUBSYSTEM_HPP
#include "control/chassis/drive/quad_drive/data/quad_drive_data.hpp"
#include "wrap/rail/chassis/iquad_drive_subsystem.hpp"
#include "wrap/rail/rail_motor_owner.hpp"

#include <memory>

namespace fang::chassis
{
    /**
     * This provides control for a set of 4 ISpeedMotors
     * It manages the initialization and update functionality
     * as well.
     *
     * This is often passed into a holonomic drive or tank drive
     * to delegate managing the wheel speeds and updating each of the motors
     *
     * This can be managed by a taproot command (can be registered).
     */
    class QuadDriveSubsystem:
        virtual public IQuadDriveSubsystem
    {
    public:

        QuadDriveSubsystem
        (
            std::unique_ptr<motor::ISpeedMotor> frontLeftMotor,
            std::unique_ptr<motor::ISpeedMotor> frontRightMotor,
            std::unique_ptr<motor::ISpeedMotor> rearLeftMotor,
            std::unique_ptr<motor::ISpeedMotor> rearRightMotor
        );

        virtual void setTargetWheelSpeeds(const QuadRPM& wheelSpeeds) override;
        virtual void initialize() override;
        virtual void refresh() override;
    private:
        std::unique_ptr<motor::ISpeedMotor> frontLeftMotor_;
        std::unique_ptr<motor::ISpeedMotor> frontRightMotor_;
        std::unique_ptr<motor::ISpeedMotor> rearLeftMotor_;
        std::unique_ptr<motor::ISpeedMotor> rearRightMotor_;
    };
}
#endif