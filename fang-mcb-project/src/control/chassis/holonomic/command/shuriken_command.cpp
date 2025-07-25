#include "shuriken_command.hpp"
#include "util/math/geometry/rotate_vector_2d.hpp"
#include "wrap/units/units_alias.hpp"
#include "system/assert/fang_assert.hpp"

#include <cassert>

namespace fang::chassis
{
    ShurikenCommand::ShurikenCommand
    (
        IHolonomicSubsystemControl& holonomicSubsystem,
        const control::turret::GimbalSubsystem& turret,
        ChassisInputHandler& input,
        const Config& config
    ):
        //MAYBE: Move FPS motion logic to separate class
        CounterStrikeCommand{holonomicSubsystem, turret, input, {config.maxTranslation, 0_rpm}},
        mk_config{config},
        mk_downscaler{config.downscaleCoefficient}
    {
    }

    const char* ShurikenCommand::getName() const
    {
        return mk_name;
    }

    void ShurikenCommand::execute()
    {
        holonomicSubsystem_.setTargetTranslation(targetFieldTranslation_);
        holonomicSubsystem_.setTargetRotation(getFieldRotation());
    }

    RPM ShurikenCommand::getFieldRotation() const
    {
        const double downscale{mk_downscaler.getDownscale(targetFieldTranslation_.getMagnitude())};
        const RPM rotation{mk_config.shurikenSpeed * downscale};
        FANG_ASSERT(rotation <= mk_config.shurikenSpeed, "The shuriken speed should only be downscaled!");
    }

    void ShurikenCommand::updateTargetFieldTranslation()
    {
        targetFieldTranslation_ = CounterStrikeCommand::getFieldTranslation();
    }
}//namespace  