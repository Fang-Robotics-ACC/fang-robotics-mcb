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
        HolonomicSubsystem& holonomicSubsystem,
        const turret::GimbalSubsystem& turret,
        ChassisInputHandler& inputHandler,
        const Config& config
    ):   
        FieldDriftCommand{holonomicSubsystem, inputHandler, config},
        gimbal_{turret},
        kConfig_{config}
    {
    }

    const char* CounterStrikeCommand::getName() const
    {
        return kName;
    }

    void CounterStrikeCommand::execute()
    {
        holonomicSubsystem_.setTargetTranslation(getFieldTranslation());
        holonomicSubsystem_.setTargetRotation(getFieldRotation());
    }

    physics::Velocity2D CounterStrikeCommand::getFieldTranslation() const
    {
        //The convert from turretwise translation to fieldwise
        const Radians turretBearing{gimbal_.getTargetFieldYaw()};
        const physics::Velocity2D fieldTranslation 
        {
            math::rotateVector2D(FieldDriftCommand::getFieldTranslation(), turretBearing)
        };
        return fieldTranslation;
    }

    RPM CounterStrikeCommand::getFieldRotation() const
    {
        //Convert the abstract rotation value into a tangible unit
        const double abstractRotation{chassisInput_.getRotation()};
        const RPM rotation{abstractRotation * kConfig_.maxRotation};

        const bool sameSignCheck{std::signbit(abstractRotation) == std::signbit(static_cast<double>(abstractRotation))};
        FANG_ASSERT(sameSignCheck, "Scaling should not invert rotation");

        return rotation;
    }
}//namespace fang::chassis