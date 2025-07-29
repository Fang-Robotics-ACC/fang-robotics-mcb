#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_QUAD_SUBSYSTEM_DRIVE_QUAD_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_QUAD_SUBSYSTEM_DRIVE_QUAD_SUBSYSTEM_HPP
#include "control/chassis/drive/quad_drive/data/quad_drive_data.hpp"
#include "wrap/rail/chassis/iquad_drive_subsystem.hpp"
#include "wrap/rail/rail_motor_owner.hpp"

#include <array>
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
        using Motor = motor::ISpeedMotor;

        QuadDriveSubsystem
        (
            std::unique_ptr<Motor> frontLeftMotor,
            std::unique_ptr<Motor> frontRightMotor,
            std::unique_ptr<Motor> rearLeftMotor,
            std::unique_ptr<Motor> rearRightMotor
        );

        virtual void setTargetWheelSpeeds(const QuadRPM& wheelSpeeds) override;
        virtual void initialize() override;
        virtual void refresh() override;
    private:
        enum class MotorIndex
        {
            frontLeft = 0,
            frontRight,
            rearLeft,
            rearRight
        };
        std::array<std::unique_ptr<Motor>, 4> motors_;
    };
}
#endif