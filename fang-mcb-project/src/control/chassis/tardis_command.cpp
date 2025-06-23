#include "tardis_command.hpp"
#include "configuration/motion_control_config.hpp"
#include "chassislogicaliases.hpp"
#include "unitaliases.hpp"
#include "rotatevector2d.hpp"

#include <cassert>

namespace control
{
    namespace chassis
    {
        TardisCommand::TardisCommand(ChassisSubsystem& chassisSubsystem, const turret::GimbalSubsystem& turret ,ChassisInputHandler& input, const Config& config)
        :   m_chassisSubsystem{chassisSubsystem},
            m_turret{turret},
            m_input{input},
            mk_config{config},
            mk_motionConfig{config.motionConfig},
            mk_downscaler{config.downscaleCoefficient},
            m_razielKalmanShredder{config.razielKalmanShredderConfig}
        {
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
            m_chassisSubsystem.setMotion(fieldTranslation, rotation);
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
            const physics::Velocity2D fieldTranslation{util::math::rotateVector2D(frameTranslation, turretBearing)};

            return fieldTranslation;
        }

        RPM TardisCommand::calculateRotation(const physics::Velocity2D fieldTranslation) const
        {
            const double downscale{mk_downscaler.getDownscale(fieldTranslation.getMagnitude())};
            const RPM rotation{mk_config.shurikenSpeed * downscale};
            return rotation;
        }


    }//namespace control
}//namespace chassis