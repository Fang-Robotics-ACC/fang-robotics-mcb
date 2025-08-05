#pragma once

#include "wrap/trap/communication/sensors/iimu.hpp"
#include "wrap/rail/turret/ifield_pitch_system.hpp"
#include "wrap/rail/motor/iposition_motor.hpp"

#include "util/math/arithmetic/range.hpp"

#include <memory>

namespace fang::turret
{
    /**
     * Dead reckoning field pitch system.
     * Assumes the robot is flat, making it technically a field pitch system
     * 
     * This clamps the pitch to prevent damage tothe robot.
     */
    class BasicFieldPitchSystem : virtual public IFieldPitchSystem 
    {
    public:
        using PitchRange = math::Range<Radians>;
        using Motor = motor::IPositionMotor;
        using Imu = trap::communication::sensors::IImu;
        /**
         * @var pitchRange - max and minimum pitch relative to the robot 
         */
        struct Config
        {
            Radians pitchError;
            PitchRange pitchRange;
        };

        BasicFieldPitchSystem
        (
            std::unique_ptr<Motor> motor,
            const Config& config
        );
        void initialize() override;
        void update() override;

        /**
         * Note that the pitch is relative to the robot
         * assuming the 0 position of the motor is flat and horizontal
         */
        void setTargetFieldPitch(const Radians& pitch) override;
    private:
        std::unique_ptr<Motor> motor_;
        const Radians kPitchError_; 
        const PitchRange kPitchRange_;
    };
}