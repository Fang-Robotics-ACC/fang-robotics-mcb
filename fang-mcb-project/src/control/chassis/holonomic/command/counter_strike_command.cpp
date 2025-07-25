#include "counter_strike_command.hpp"
#include "util/math/geometry/rotate_vector_2d.hpp"
#include "wrap/units/units_alias.hpp"

#include "modm/architecture/interface/assert.hpp"

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
    {}

    bool CounterStrikeCommand::isFinished() const
    {
        return false;
    }

    physics::Velocity2D CounterStrikeCommand::getFieldTranslation() const
    {
        const math::AbstractVector2D turretFrameTranslation{chassisInput_.getTranslation()};
        //It must be converted to a tangible value via scaling
        const physics::Velocity2D frameTranslation{turretFrameTranslation.x * kConfig_.maxXTranslation, turretFrameTranslation.y * kConfig_.maxYTranslation};

        //Invariant assertions: these should NEVER be violated
        {
            //If the turret frame translation is positive, the frame translation must be positive
            //Because the configuration scalars must be positive themselves
            math::Vector2D<bool> turretFrameTranslationSigns
            {
                std::signbit(turretFrameTranslation.x),
                std::signbit(turretFrameTranslation.y)
            };

            math::Vector2D<bool> frameTranslationSigns 
            {
                std::signbit(frameTranslation.x),
                std::signbit(frameTranslation.y)
            };
            //These will be optimized away on performance builds
            const bool sameSignCheckX{turretFrameTranslationSigns.x == frameTranslationSigns.x};
            const bool sameSignCheckY{turretFrameTranslationSigns.y == frameTranslationSigns.y};

            modm_assert(sameSignCheckX, "CounterStrikeCommand.getFieldTraslation.sameSign.x", "Scaling should not invert motion");
            modm_assert(sameSignCheckY, "CounterStrikeCommand.getFieldTraslation.sameSign.y", "Scaling should not invert motion");
        }

        const Radians turretBearing{gimbal_.getTargetFieldYaw()};

        const physics::Velocity2D fieldTranslation{math::rotateVector2D(frameTranslation, turretBearing)};
        return fieldTranslation;
    }

    RPM CounterStrikeCommand::getFieldRotation() const
    {
        //Convert the abstract rotation value into a tangible unit
        const double abstractRotation{chassisInput_.getRotation()};
        const RPM rotation{abstractRotation * kConfig_.maxRotation};

        const bool sameSignCheck{std::signbit(abstractRotation) == std::signbit(static_cast<double>(abstractRotation))};
        modm_assert(sameSignCheck, "CounterStrikeCommand.getFieldRotation.sameSign", "Scaling should not invert rotation");

        return rotation;
    }
}//namespace fang::chassis