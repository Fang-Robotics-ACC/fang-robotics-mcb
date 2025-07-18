#include "shuriken_command.hpp"
#include "util/math/geometry/rotate_vector_2d.hpp"
#include "wrap/units/units_alias.hpp"

#include <cassert>

namespace control
{
    namespace chassis
    {
        ShurikenCommand::ShurikenCommand(ChassisSubsystem& chassisSubsystem, const turret::GimbalSubsystem& turret ,ChassisInputHandler& input, const Config& config)
        :   m_chassisSubsystem{chassisSubsystem},
            m_turret{turret},
            m_input{input},
            mk_config{config},
            mk_motionConfig{config.motionConfig},
            mk_downscaler{config.downscaleCoefficient}
        {
            addSubsystemRequirement(&m_chassisSubsystem);
        }

        const char* ShurikenCommand::getName() const
        {
            return mk_name;
        }

        void ShurikenCommand::initialize()
        {
        }

        void ShurikenCommand::execute()
        {
            switch(m_controlMode)
            {
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

        void ShurikenCommand::end(bool interrupted)
        {}

        bool ShurikenCommand::isFinished() const
        {
            return false;
        }

        void ShurikenCommand::executeRemoteTestStrafeTurret()
        {

            const math::AbstractVector2D abstractTranslation{m_input.getTranslation()};
            const physics::Velocity2D frameTranslation{abstractTranslation.x * mk_motionConfig.maxXTranslation, abstractTranslation.y * mk_motionConfig.maxYTranslation};
            const Radians turretBearing{m_turret.getTargetFieldYaw()};

            const physics::Velocity2D fieldTranslation{math::rotateVector2D(frameTranslation, turretBearing)};

            const double downscale{mk_downscaler.getDownscale(fieldTranslation.getMagnitude())};
            const RPM rotation{mk_config.shurikenSpeed * downscale};
            m_chassisSubsystem.setMotion(fieldTranslation, rotation);
        }

        void ShurikenCommand::executeKeyboardTestFieldRotate()
        {}

        void ShurikenCommand::executeKeyboardTestStrafeTurret()
        {}
    }//namespace control
}//namespace chassis