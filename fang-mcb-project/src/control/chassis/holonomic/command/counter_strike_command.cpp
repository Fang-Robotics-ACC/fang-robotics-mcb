#include "counter_strike_command.hpp"
#include "util/math/geometry/rotate_vector_2d.hpp"
#include "wrap/units/units_alias.hpp"

#include "modm/architecture/interface/assert.hpp"
#include "system/assert/fang_assert.hpp"

#include <cmath>

namespace fang::chassis
{
    CounterStrikeCommand::CounterStrikeCommand
    (
        IHolonomicSubsystemControl& chassisSubsystem,
        const control::turret::GimbalSubsystem& turret,
        ChassisInputHandler& inputHandler,
        const Config& config
    ):   
        holonomicSubsystem_{chassisSubsystem},
        gimbal_{turret},
        chassisInput_{inputHandler},
        kConfig_{config}
    {
        addSubsystemRequirement(&holonomicSubsystem_);
    }

    const char* CounterStrikeCommand::getName() const
    {
        return kName;
    }

    void CounterStrikeCommand::initialize()
    {
    }

    void CounterStrikeCommand::execute()
    {
        holonomicSubsystem_.setTargetTranslation(getFieldTranslation());
        holonomicSubsystem_.setTargetRotation(getFieldRotation());
    }

    void CounterStrikeCommand::end(bool interrupted)
    {
    }

    bool CounterStrikeCommand::isFinished() const
    {
        return false;
    }

    physics::Velocity2D CounterStrikeCommand::getFieldTranslation() const
    {
        //The convert from turretwise translation to fieldwise
        const math::AbstractVector2D turretwiseTranslation{chassisInput_.getTranslation()};
        const Radians turretBearing{gimbal_.getTargetFieldYaw()};
        const math::AbstractVector2D abstractFieldTranslation
        {
            math::rotateVector2D(turretwiseTranslation, turretBearing)
        };

        //It must be converted to a tangible value via scaling
        const physics::Velocity2D fieldTranslation
        {
            abstractFieldTranslation.x * kConfig_.maxXTranslation, 
            abstractFieldTranslation.y * kConfig_.maxYTranslation
        };

        assertGetFieldTranslationUniformSigns(abstractFieldTranslation, fieldTranslation);

        return fieldTranslation;
    }

    void CounterStrikeCommand::assertGetFieldTranslationUniformSigns
    (
        const math::AbstractVector2D& abstractFieldTranslation,
        const physics::Velocity2D& fieldTranslation
    )
    const
    {
        //If the turret frame translation is positive, the frame translation must be positive
        //Because the configuration scalars must be positive themselves
        //These will be optimized away on performance builds
        math::Vector2D<bool> turretFrameTranslationSigns
        {
            std::signbit(abstractFieldTranslation.x),
            std::signbit(abstractFieldTranslation.y)
        };

        math::Vector2D<bool> frameTranslationSigns 
        {
            std::signbit(fieldTranslation.x),
            std::signbit(fieldTranslation.y)
        };

        const bool sameSignCheckX{turretFrameTranslationSigns.x == frameTranslationSigns.x};
        const bool sameSignCheckY{turretFrameTranslationSigns.y == frameTranslationSigns.y};

        FANG_ASSERT(sameSignCheckX, "CounterStrikeCommand.getFieldTraslation.sameSign.x", "Scaling should not invert motion");
        FANG_ASSERT(sameSignCheckY, "CounterStrikeCommand.getFieldTraslation.sameSign.y", "Scaling should not invert motion");
    }

    RPM CounterStrikeCommand::getFieldRotation() const
    {
        //Convert the abstract rotation value into a tangible unit
        const double abstractRotation{chassisInput_.getRotation()};
        const RPM rotation{abstractRotation * kConfig_.maxRotation};

        const bool sameSignCheck{std::signbit(abstractRotation) == std::signbit(static_cast<double>(abstractRotation))};
        FANG_ASSERT(sameSignCheck, "CounterStrikeCommand.getFieldRotation.sameSign", "Scaling should not invert rotation");

        return rotation;
    }
}//namespace fang::chassis