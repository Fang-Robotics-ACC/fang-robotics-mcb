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
        holonomicSubsystem_.setTargetTranslation(targetFieldTranslation_);
        holonomicSubsystem_.setTargetRotation(getFieldRotation());
    }

    RPM ShurikenCommand::getFieldRotation() const
    {
        const double downscale{kDownscaler_.getDownscale(targetFieldTranslation_.getMagnitude())};
        const RPM rotation{kConfig_.shurikenSpeed * downscale};
        FANG_ASSERT(rotation <= kConfig_.shurikenSpeed, "The shuriken speed should only be downscaled!");
        return rotation;
    }

    void ShurikenCommand::updateTargetFieldTranslation()
    {
        targetFieldTranslation_ = CounterStrikeCommand::getFieldTranslation();
    }
}//namespace  