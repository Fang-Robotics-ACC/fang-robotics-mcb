#ifndef FANG_ROBOTICS_MCB_FIELD_MECANUM_COMMAND_HPP
#define FANG_ROBOTICS_MCB_FIELD_MECANUM_COMMAND_HPP
#include "control/chassis/chassis_input_handler.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "control/turret/gimbal_subsystem.hpp"

#include "tap/control/command.hpp"

namespace fang::chassis
{
    /**
     * This intermediates the inputs and the mecanum drive 
     */
    class FieldMecanumCommand: public tap::control::Command
    {
    public:
    struct Config
    {
        MetersPerSecond maxTranslation;
        MetersPerSecond maxXTranslation;
        MetersPerSecond maxYTranslation;
        RPM maxRotation;
        Degrees maxAngularDisplacement;
    };
    /**
     * Remote uses the dji controller.
     * Keyboard uses the keyboard inputs.
     * TEST_FIELD_ROTATE = The horizontal right joystick or mouse causes the chassis to rotate.
     * TEST_STAFE_TURRET = The chassis will only translate, leaving the horizontal mouse or right joystick
     * input for the turret.
     */
    enum class ControlMode
    {
        REMOTE_TEST_FIELD_ROTATE,
        REMOTE_TEST_STRAFE_TURRET,
        KEYBOARD_TEST_FIELD_ROTATE,
        KEYBOARD_TEST_STRAFE_TURRET
    };
        /**
         * This takes a chassis subsystem and the respective inputHandler
         */
        FieldMecanumCommand(ChassisSubsystem& chassisSubsystem, const control::turret::GimbalSubsystem& turret ,ChassisInputHandler& inputHandler, const Config& config);
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
        static constexpr char* mk_name{"Chassis tank drive"};
        ChassisSubsystem& m_chassisSubsystem;
        const control::turret::GimbalSubsystem& m_gimbal; //We don't want the command to alter the turret state
        ChassisInputHandler& m_input;
        ControlMode m_controlMode{ControlMode::REMOTE_TEST_STRAFE_TURRET};
        const Config& mk_config;
    };
}//namespace chassis
#endif