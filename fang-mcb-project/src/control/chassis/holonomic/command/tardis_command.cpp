#include "tardis_command.hpp"
#include "wrap/units/units_alias.hpp"
#include "util/math/geometry/rotate_vector_2d.hpp"

#include <cassert>

namespace fang::chassis 
{
    TardisCommand::TardisCommand
    (
        IHolonomicSubsystemControl& chassisSubsystem,
        const control::turret::GimbalSubsystem& turret,
        ChassisInputHandler& input,
        const Config& config
    ):
        ShurikenCommand
        {
            chassisSubsystem,
            turret,
            input,
            ShurikenCommand::Config
            {
                .maxTranslation = config.maxTranslation,
                .shurikenSpeed  = config.maxRotation,
                .downscaleCoefficient = config.downscaleCoefficient
            }
        },
        mk_config{config},
        m_razielKalmanShredder{config.razielKalmanShredderConfig}
    {
        m_kalmanTimer.reset();
    }

    const char* TardisCommand::getName() const
    {
        return mk_name;
    }

    void TardisCommand::execute()
    {
        holonomicSubsystem_.setTargetTranslation(CounterStrikeCommand::getFieldTranslation());
        holonomicSubsystem_.setTargetRotation(getFieldRotation());
    }

    RPM TardisCommand::getFieldRotation() const
    {
        const Seconds now{m_kalmanTimer.getDuration()};
        const double razielShredderDownscale{m_razielKalmanShredder.getScalingFactor(static_cast<double>(now))};
        const RPM rotation{ShurikenCommand::getFieldRotation() * razielShredderDownscale};
        return rotation;
    }
}