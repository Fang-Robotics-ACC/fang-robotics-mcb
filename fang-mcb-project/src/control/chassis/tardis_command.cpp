#include "tardis_command.hpp"
#include "wrap/units/units_alias.hpp"
#include "util/math/geometry/rotate_vector_2d.hpp"

#include <cassert>

namespace fang::chassis 
{
    TardisCommand::TardisCommand(IHolonomicSubsystemControl& chassisSubsystem, const control::turret::GimbalSubsystem& turret ,ChassisInputHandler& input, const Config& config)
    :   m_chassisSubsystem{chassisSubsystem},
        m_turret{turret},
        m_input{input},
        mk_config{config},
        mk_motionConfig{config.motionConfig},
        mk_downscaler{config.downscaleCoefficient},
        m_razielKalmanShredder{config.razielKalmanShredderConfig}
    {
        m_kalmanTimer.reset();
        addSubsystemRequirement(&m_chassisSubsystem);
    }

    const char* TardisCommand::getName() const
    {
        return mk_name;
    }

    void TardisCommand::initialize()
    {
    }

    void TardisCommand::execute()
    {
        const physics::Velocity2D fieldTranslation{calcuateFieldTranslation()};
        const RPM rotation{calculateRotation(fieldTranslation)};

        m_chassisSubsystem.setTargetTranslation(fieldTranslation);
        m_chassisSubsystem.setTargetRotation(rotation);
    }

    void TardisCommand::end(bool interrupted)
    {}

    bool TardisCommand::isFinished() const
    {
        return false;
    }

    physics::Velocity2D TardisCommand::calcuateFieldTranslation() const
    {
        const math::AbstractVector2D abstractTranslation{m_input.getTranslation()};
        const physics::Velocity2D frameTranslation{abstractTranslation.x * mk_motionConfig.maxXTranslation, abstractTranslation.y * mk_motionConfig.maxYTranslation};
        const Radians turretBearing{m_turret.getTargetFieldYaw()};
        const physics::Velocity2D fieldTranslation{math::rotateVector2D(frameTranslation, turretBearing)};

        return fieldTranslation;
    }

    RPM TardisCommand::calculateRotation(const physics::Velocity2D fieldTranslation) const
    {
        const Seconds now{m_kalmanTimer.getDuration()};
        const double razielShredderDownscale{m_razielKalmanShredder.getScalingFactor(static_cast<double>(now))};
        const double downscale{mk_downscaler.getDownscale(fieldTranslation.getMagnitude())};
        const RPM rotation{mk_config.shurikenSpeed * downscale * razielShredderDownscale};
        return rotation;
    }
}