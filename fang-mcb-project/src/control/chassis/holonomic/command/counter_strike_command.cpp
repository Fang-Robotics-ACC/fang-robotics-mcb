#include "counter_strike_command.hpp"
#include "util/math/geometry/rotate_vector_2d.hpp"
#include "wrap/units/units_alias.hpp"

#include <cassert>

namespace fang::chassis
{
    CounterStrikeCommand::CounterStrikeCommand(IHolonomicSubsystemControl& chassisSubsystem, const control::turret::GimbalSubsystem& turret ,ChassisInputHandler& inputHandler, const Config& config)
    :   m_chassisSubsystem{chassisSubsystem},
        m_gimbal{turret},
        m_input{inputHandler},
        mk_config{config}
    {
        addSubsystemRequirement(&m_chassisSubsystem);
    }

    const char* CounterStrikeCommand::getName() const
    {
        return mk_name;
    }

    void CounterStrikeCommand::initialize()
    {
    }

    void CounterStrikeCommand::execute()
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

    void CounterStrikeCommand::end(bool interrupted)
    {}

    bool CounterStrikeCommand::isFinished() const
    {
        return false;
    }

    void CounterStrikeCommand::executeRemoteTestFieldRotate()
    {
        const math::AbstractVector2D abstractTranslation{m_input.getTranslation()};
        const double abstractRotation{m_input.getRotation()};

        const physics::Velocity2D translation{abstractTranslation.x * mk_config.maxXTranslation, abstractTranslation.y * mk_config.maxYTranslation};
        const RPM rotation{abstractRotation * mk_config.maxRotation};

        m_chassisSubsystem.setTargetTranslation(translation);
        m_chassisSubsystem.setTargetRotation(rotation);
    }

    void CounterStrikeCommand::executeRemoteTestStrafeTurret()
    {

        const math::AbstractVector2D abstractTranslation{m_input.getTranslation()};
        const physics::Velocity2D frameTranslation{abstractTranslation.x * mk_config.maxXTranslation, abstractTranslation.y * mk_config.maxYTranslation};
        const Radians turretBearing{m_gimbal.getTargetFieldYaw()};

        const physics::Velocity2D fieldTranslation{math::rotateVector2D(frameTranslation, turretBearing)};

        const double abstractRotation{m_input.getRotation()};

        const RPM rotation{abstractRotation * mk_config.maxRotation};

        m_chassisSubsystem.setTargetTranslation(fieldTranslation);
        m_chassisSubsystem.setTargetRotation(rotation);
    }

    void CounterStrikeCommand::executeKeyboardTestFieldRotate()
    {}

    void CounterStrikeCommand::executeKeyboardTestStrafeTurret()
    {}
}//namespace fang::chassis