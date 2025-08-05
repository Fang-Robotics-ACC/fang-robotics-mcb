#include "tardis_command.hpp"
#include "wrap/units/units_alias.hpp"
#include "util/math/geometry/rotate_vector_2d.hpp"

#include <cassert>

namespace fang::chassis 
{
    using namespace units::literals;
    TardisCommand::TardisCommand
    (
        HolonomicSubsystem& chassisSubsystem,
        const turret::FieldGimbalSubsystem& turret,
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
        kConfig_{config},
        razielKalmanShredder_{config.razielKalmanShredderConfig}
    {
        kShredderTimer.reset();
    }

    const char* TardisCommand::getName() const
    {
        return kName;
    }

    void TardisCommand::execute()
    {
        holonomicSubsystem_.setTargetTranslation(CounterStrikeCommand::getFieldTranslation());
        holonomicSubsystem_.setTargetRotation(getFieldRotation());
    }

    RPM TardisCommand::getFieldRotation() const
    {
        const Seconds now{kShredderTimer.getDuration()};
        const double razielShredderDownscale{razielKalmanShredder_.getScalingFactor(static_cast<double>(now))};
        const RPM rotation{ShurikenCommand::getFieldRotation() * razielShredderDownscale};
        return rotation;
    }
}