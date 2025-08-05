#include "basic_field_pitch_system.hpp"
#include "tap/algorithms/math_user_utils.hpp"

namespace fang::turret
{

    BasicFieldPitchSystem::BasicFieldPitchSystem
    (
        std::unique_ptr<Motor> motor,
        const Config& config
    ):
        motor_{std::move(motor)},
        kPitchError_{config.pitchError},
        kPitchRange_{config.pitchRange}
    {
    }

    void BasicFieldPitchSystem::initialize()
    {
        motor_->initialize();
    }

    void BasicFieldPitchSystem::update()
    {
        motor_->update();
    }

    void BasicFieldPitchSystem::setTargetFieldPitch(const Radians& pitch)
    {
        // The pitch is relative to the robot
        // Fist correct the pitch so that the input is being considered
        // Ensure the pitch is within the proper ranges to prevent damage
        const Radians kClampedPitch
        {
            tap::algorithms::limitVal(pitch, kPitchRange_.min, kPitchRange_.max)
        };

        // Relative to the robot. (Remember, this assumes the robot is flat)
        // If the zero position of the motor is 5 degrees counterclockwise
        // to the field pitch zero, the error would be 5 degrees counterclockwise
        // Thus, the fed position towards the turret would be -5 degrees counterclockwise
        const Radians kRobotPitch{kClampedPitch - kPitchError_};
        
        motor_->setTargetPosition(kRobotPitch);
    }
}