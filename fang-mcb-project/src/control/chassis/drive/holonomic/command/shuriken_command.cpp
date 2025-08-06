#include "shuriken_command.hpp"
#include "util/math/geometry/rotate_vector_2d.hpp"
#include "wrap/units/units_alias.hpp"
#include "system/assert/fang_assert.hpp"

#include <cassert>

namespace fang::chassis
{
    using namespace units::literals;
    ShurikenCommand::ShurikenCommand
    (
        HolonomicSubsystem& holonomicSubsystem,
        const turret::FieldGimbalSubsystem& gimbal,
        ChassisInputHandler& input,
        const Config& config
    ):
        //MAYBE: Move FPS motion logic to separate class
        //1 so that zero max rotation erro is not happening
        CounterStrikeCommand{holonomicSubsystem, gimbal, input, {config.maxTranslation, 1_rpm}},
        kConfig_{config},
        kDownscaler_{config.downscaleCoefficient}
    {
    }

    const char* ShurikenCommand::getName() const
    {
        return kName;
    }

    void ShurikenCommand::execute()
    {
        const physics::Velocity2D kTargetFieldTranslation{CounterStrikeCommand::getFieldTranslation()};
        holonomicSubsystem_.setTargetTranslation(kTargetFieldTranslation);
        holonomicSubsystem_.setTargetRotation(getFieldRotation(kTargetFieldTranslation));
    }

    RPM ShurikenCommand::getFieldRotation(const physics::Velocity2D& targetFieldTranslation) const
    {
        const double downscale{kDownscaler_.getDownscale(targetFieldTranslation.getMagnitude())};
        const RPM rotation{kConfig_.shurikenSpeed * downscale};
        FANG_ASSERT(rotation <= kConfig_.shurikenSpeed, "The shuriken speed should only be downscaled!");
        return rotation;
    }
}