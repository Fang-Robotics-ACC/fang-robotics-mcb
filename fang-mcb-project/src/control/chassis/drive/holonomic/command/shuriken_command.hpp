#pragma once

#include "counter_strike_command.hpp"
#include "control/chassis/algorithms/basic_downscaler.hpp"

#include "tap/control/command.hpp"

namespace fang::chassis 
{
    /**
     * The holonomic drive will automatically spin
     */
    class ShurikenCommand: public CounterStrikeCommand
    {
    public:
        using MotionConfig = CounterStrikeCommand::Config;
        /**
         * Positive shuriken speed is counterclockwise
         *
         * The higher the downscale coefficient, the less it will downscale with respect to speed
         */
        struct Config
        {
            physics::Velocity2D maxTranslation;
            RPM shurikenSpeed;
            double downscaleCoefficient;
        };
        /**
         * This takes a chassis subsystem and the respective inputHandler
         */
        ShurikenCommand
        (
            HolonomicSubsystem& chassisSubsystem,
            const turret::FieldGimbalSubsystem& gimbal,
            DjiHolonomicInput& input,
            const Config& config
        );
        virtual ~ShurikenCommand() = default;
        const char* getName() const override;
        void execute() override;
    protected:
        /**
         * Translates the rotation input on the remote into
         * a rotation where counterclockwise is positive
         * 
         * It also downscales the angular velocity inversly
         * proportional to the targetFieldTranslation
         */
        RPM getFieldRotation(const physics::Velocity2D& targetFieldTranslation) const;

    private:
        static constexpr const char* kName{"Shuriken"};

        const Config kConfig_;
        const BasicDownscaler kDownscaler_;
    };
}