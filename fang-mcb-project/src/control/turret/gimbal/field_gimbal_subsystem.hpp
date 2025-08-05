#pragma once

#include "wrap/rail/turret/ifield_gimbal.hpp"
#include "wrap/rail/turret/ifield_pitch_info.hpp"
#include "wrap/rail/turret/ifield_gimbal_info.hpp"

#include "tap/drivers.hpp"
#include "tap/control/subsystem.hpp"

namespace fang::turret
{
    class FieldGimbalSubsystem:
        virtual public IFieldGimbal,
        virtual public IFieldGimbalInfo,
        public tap::control::Subsystem
    {
    public:
        FieldGimbalSubsystem(tap::Drivers& drivers):
            Subsystem{&drivers}
        {}
        virtual ~FieldGimbalSubsystem() {};

        //Prevent ambiguity errors
        virtual void initialize() = 0;
    };
}