#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_SHURIKEN_COMMAND_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_HOLONOMIC_COMMAND_SHURIKEN_COMMAND_HPP
#include "counter_strike_command.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "control/chassis/algorithms/basic_downscaler.hpp"

#include "control/turret/gimbal_subsystem.hpp"


#include "tap/control/command.hpp"

namespace fang::chassis 
{
    /**
     * The chassis will spin in the desired direction. It will use turret oriented strafe.
     */
    class ShurikenCommand: public CounterStrikeCommand
    {
    public:
        using MotionConfig = CounterStrikeCommand::Config;
        /**
         * Remote uses the dji controller.
         * Keyboard uses the keyboard inputs.
         * TEST_FIELD_ROTATE = The horizontal right joystick or mouse causes the chassis to rotate.
         * TEST_STAFE_TURRET = The chassis will only translate, leaving the horizontal mouse or right joystick
         * input for the turret.
         */
        /**
         * Positive shuriken speed is counterclockwise
         *
         * The higher the downscale coefficient, the less it will downscale with respect to speed
         */
        struct Config
        {
            RPM shurikenSpeed;
            MotionConfig motionConfig;
            double downscaleCoefficient;
        };
        /**
         * This takes a chassis subsystem and the respective inputHandler
         */
        ShurikenCommand(IHolonomicSubsystemControl& chassisSubsystem, const control::turret::GimbalSubsystem& turret ,ChassisInputHandler& input, const Config& config);
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
        static constexpr char* mk_name{"Shuriken Mode"};
        const Config mk_config;
        const BasicDownscaler mk_downscaler;

        physics::Velocity2D targetFieldTranslation_{};
    };
}
#endif