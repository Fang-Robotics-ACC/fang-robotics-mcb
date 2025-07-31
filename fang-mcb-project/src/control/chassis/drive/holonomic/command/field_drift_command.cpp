#include "field_drift_command.hpp"
#include "util/math/geometry/rotate_vector_2d.hpp"
#include "wrap/units/units_alias.hpp"

#include "modm/architecture/interface/assert.hpp"
#include "system/assert/fang_assert.hpp"

#include <cmath>

namespace fang::chassis
{
    FieldDriftCommand::FieldDriftCommand
    (
        IHolonomicSubsystem& chassisSubsystem,
        ChassisInputHandler& inputHandler,
        const Config& config
    ):   
        holonomicSubsystem_{chassisSubsystem},
        chassisInput_{inputHandler},
        kConfig_{config}
    {
        assertConfigValues(config);
        addSubsystemRequirement(holonomicSubsystem_);
    }

    const char* FieldDriftCommand::getName() const
    {
        return kName;
    }

    void FieldDriftCommand::initialize()
    {
    }

    void FieldDriftCommand::execute()
    {
        holonomicSubsystem_.setTargetTranslation(getFieldTranslation());
        holonomicSubsystem_.setTargetRotation(getFieldRotation());
    }

    void FieldDriftCommand::end(bool interrupted)
    {
    }

    bool FieldDriftCommand::isFinished() const
    {
        return false;
    }

    physics::Velocity2D FieldDriftCommand::getFieldTranslation() const
    {
        //The convert from turretwise translation to fieldwise
        const math::AbstractVector2D abstractFieldTranslation{chassisInput_.getTranslation()};
        //It must be converted to a tangible value via scaling
        const physics::Velocity2D fieldTranslation
        {
            abstractFieldTranslation.x * kConfig_.maxTranslation.x,
            abstractFieldTranslation.y * kConfig_.maxTranslation.y
        };

        assertGetFieldTranslationUniformSigns(abstractFieldTranslation, fieldTranslation);

        return fieldTranslation;
    }

    void FieldDriftCommand::assertConfigValues(const Config& config)
    {
        FANG_ASSERT(config.maxTranslation.x >= 0_mps, "maxTranslation.x cannot be negative");
        FANG_ASSERT(config.maxTranslation.y >= 0_mps, "maxTranslation.y cannot be negative");
    }

    void FieldDriftCommand::assertGetFieldTranslationUniformSigns
    (
        const math::AbstractVector2D& abstractFieldTranslation,
        const physics::Velocity2D& fieldTranslation
    )
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

        FANG_ASSERT(sameSignCheckX, "Scaling should not invert motion");
        FANG_ASSERT(sameSignCheckY, "Scaling should not invert motion");
    }

    RPM FieldDriftCommand::getFieldRotation() const
    {
        //Convert the abstract rotation value into a tangible unit
        const double abstractRotation{chassisInput_.getRotation()};
        const RPM rotation{abstractRotation * kConfig_.maxRotation};

        const bool sameSignCheck{std::signbit(abstractRotation) == std::signbit(static_cast<double>(abstractRotation))};
        FANG_ASSERT(sameSignCheck, "Scaling should not invert rotation");

        return rotation;
    }
}//namespace fang::chassis