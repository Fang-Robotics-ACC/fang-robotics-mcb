#ifndef FANG_ROBOTICS_MCB_SHURIKEN_COMMAND_HPP
#define FANG_ROBOTICS_MCB_SHURIKEN_COMMAND_HPP
#include "control/input_handler.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "control/chassis/field_mecanum_command.hpp"
#include "control/turret/gimbal_subsystem.hpp"

#include "tap/control/command.hpp"

namespace control
{
    namespace chassis
    {
        /**
         * The chassis will spin in the desired direction. It will use turret oriented strafe.
         */
        class ShurikenCommand: public tap::control::Command
        {
        public:
        using MotionConfig = FieldMecanumCommand::Config;
        /**
         * Remote uses the dji controller.
         * Keyboard uses the keyboard inputs.
         * TEST_FIELD_ROTATE = The horizontal right joystick or mouse causes the chassis to rotate.
         * TEST_STAFE_TURRET = The chassis will only translate, leaving the horizontal mouse or right joystick
         * input for the turret.
         */
        /**
         * Positive shuriken speed is counterclockwise
         */
        struct Config
        {
            RPM shurikenSpeed;
            MotionConfig motionConfig;
        };
        enum class ControlMode
        {
            REMOTE_TEST_STRAFE_TURRET,
            KEYBOARD_TEST_FIELD_ROTATE,
            KEYBOARD_TEST_STRAFE_TURRET
        };
            /**
             * This takes a chassis subsystem and the respective inputHandler
             */
            ShurikenCommand(ChassisSubsystem& chassisSubsystem, const turret::GimbalSubsystem& turret ,ChassisInputHandler& input, const Config& config);
            const char* getName() const override;
            void initialize() override;
            void execute() override;
            void end(bool interrupted) override;
            bool isFinished() const;
        private:
            void executeRemoteTestFieldRotate();
            void executeRemoteTestStrafeTurret();
            void executeKeyboardTestFieldRotate();
            void executeKeyboardTestStrafeTurret();
            static constexpr char* mk_name{"Shuriken Mode"};
            ChassisSubsystem& m_chassisSubsystem;
            const turret::GimbalSubsystem& m_turret; //We don't want the command to alter the turret state
            ChassisInputHandler& m_input;
            ControlMode m_controlMode{ControlMode::REMOTE_TEST_STRAFE_TURRET};
            const Config mk_config;
            const MotionConfig mk_motionConfig;
        };
    }//namespace control
}//namespace chassis
#endif