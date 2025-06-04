#include "field_mecanum_command.hpp"
#include "configuration/motion_control_config.hpp"
#include "chassislogicaliases.hpp"
#include "unitaliases.hpp"

#include <cassert>

namespace control
{
    namespace chassis
    {
        FieldMecanumCommand::FieldMecanumCommand(ChassisSubsystem& chassisSubsystem, InputHandler& inputHandler, const config::motion::MotionConfig& motionConfig)
        : m_chassisSubsystem{chassisSubsystem}, m_inputHandler{inputHandler}, mk_motionConfig{motionConfig};
        {}

        const char* FieldMecanumCommand::getName() const
        {
            return mk_name;
        }

        void FieldMecanumCommand::initialize()
        {

        }

        void FieldMecanumCommand::execute()
        {
            switch(m_controlMode)
            {
                case ControlMode::REMOTE_TEST_FIELD_ROTATE:
                    executeRemoteTestFieldRotate();
                    break;
                case ControlMode::REMOTE_TEST_STRAFE_TURRET:
                    executeRemoteTestStrafeTurret();
                    break;
                case ControlMode::KEYBOARD_TEST_FIELD_ROTATE:
                    executeKeyboardTestFieldRotate();
                    break;
                case ControlMode::KEYBOARD_TEST_STRAFE_TURRET:
                    executeKeyboardTestStrafeTurret();
                    break;
                default:
                    assert(!"Unexpected or unsupported mode.");
            }
        }

        void FieldMecanumCommand::end(bool interrupted)
        {}

        bool FieldMecanumCommand::isFinished() const
        {
            return false;
        }

        void FieldMecanumCommand::executeRemoteTestFieldRotate()
        {
            const logic::chassis::Velocity2D translation{m_inputHandler.getChassisInputs().getRemoteTranslation()};
            const RPM rotation{m_inputHandler.getChassisInputs().getRemoteRotation()};
            m_chassisSubsystem.setMotion(translation, rotation);
        }

        void FieldMecanumCommand::executeRemoteTestStrafeTurret()
        {
            const logic::chassis::Velocity2D translation{m_inputHandler.getChassisInputs().getRemoteTranslation()};
            const RPM rotation{0};
            m_chassisSubsystem.setMotion(translation, rotation);
        }

        void FieldMecanumCommand::executeKeyboardTestFieldRotate()
        {}

        void FieldMecanumCommand::executeKeyboardTestStrafeTurret()
        {}
    }//namespace control
}//namespace chassis