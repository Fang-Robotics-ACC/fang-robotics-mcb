#include "field_mecanum_command.hpp"
#include "util/math/geometry/rotate_vector_2d.hpp"
#include "wrap/units/units_alias.hpp"

#include <cassert>

namespace control
{
    namespace chassis
    {
        FieldMecanumCommand::FieldMecanumCommand(ChassisSubsystem& chassisSubsystem, const turret::GimbalSubsystem& turret ,ChassisInputHandler& inputHandler, const Config& config)
        :   m_chassisSubsystem{chassisSubsystem},
            m_gimbal{turret},
            m_input{inputHandler},
            mk_config{config}
        {
            addSubsystemRequirement(&m_chassisSubsystem);
        }

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
            const math::AbstractVector2D abstractTranslation{m_input.getTranslation()};
            const double abstractRotation{m_input.getRotation()};

            const physics::Velocity2D translation{abstractTranslation.x * mk_config.maxXTranslation, abstractTranslation.y * mk_config.maxYTranslation};
            const RPM rotation{abstractRotation * mk_config.maxRotation};
            m_chassisSubsystem.setMotion(translation, rotation);
        }

        void FieldMecanumCommand::executeRemoteTestStrafeTurret()
        {

            const math::AbstractVector2D abstractTranslation{m_input.getTranslation()};
            const physics::Velocity2D frameTranslation{abstractTranslation.x * mk_config.maxXTranslation, abstractTranslation.y * mk_config.maxYTranslation};
            const Radians turretBearing{m_gimbal.getTargetFieldYaw()};

            const physics::Velocity2D fieldTranslation{math::rotateVector2D(frameTranslation, turretBearing)};

            const double abstractRotation{m_input.getRotation()};

            const RPM rotation{abstractRotation * mk_config.maxRotation};
            m_chassisSubsystem.setMotion(fieldTranslation, rotation);
        }

        void FieldMecanumCommand::executeKeyboardTestFieldRotate()
        {}

        void FieldMecanumCommand::executeKeyboardTestStrafeTurret()
        {}
    }//namespace control
}//namespace chassis