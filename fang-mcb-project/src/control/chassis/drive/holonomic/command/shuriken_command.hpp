#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_SHURIKEN_COMMAND_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_SHURIKEN_COMMAND_HPP
#include "counter_strike_command.hpp"
#include "control/chassis/algorithms/basic_downscaler.hpp"

#include "control/turret/gimbal_subsystem.hpp"


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
            const turret::GimbalSubsystem& gimbal,
            ChassisInputHandler& input,
            const Config& config
        );
        virtual ~ShurikenCommand() = default;
        const char* getName() const override;
        void execute() override;
    protected:
        /**
         * Translates the rotation input on the remote into
         * a rotation where counterclockwise is positive
         */
        RPM getFieldRotation() const;
        void updateTargetFieldTranslation();

    private:
        static constexpr char* kName{"Shuriken"};

        const Config kConfig_;
        const BasicDownscaler kDownscaler_;
        physics::Velocity2D targetFieldTranslation_{};
    };
}
#endif