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
        const physics::Velocity2D kTargetFieldTranslation{CounterStrikeCommand::getFieldTranslation()};
        holonomicSubsystem_.setTargetTranslation(kTargetFieldTranslation);
        holonomicSubsystem_.setTargetRotation(getFieldRotation(kTargetFieldTranslation));
    }

    RPM TardisCommand::getFieldRotation(const physics::Velocity2D& targetFieldTranslation) const
    {
        const Seconds now{kShredderTimer.getDuration()};
        const double razielShredderDownscale{razielKalmanShredder_.getScalingFactor(static_cast<double>(now))};
        const RPM rotation{ShurikenCommand::getFieldRotation(targetFieldTranslation) * razielShredderDownscale};
        return rotation;
    }
}