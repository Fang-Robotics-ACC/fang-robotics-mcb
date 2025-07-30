#ifndef FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSI_I_QUAD_DRIVE_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSI_I_QUAD_DRIVE_SUBSYSTEM_HPP

#include "wrap/rail/chassis/iquad_control.hpp"
#include "tap/control/subsystem.hpp"

namespace fang::chassis
{
    class IQuadDriveSubsystem:
        public IQuadControl,
        public tap::control::Subsystem
    {
    public:
        IQuadDriveSubsystem(tap::Drivers& drivers):
            Subsystem{&drivers}
        {}

        virtual ~IQuadDriveSubsystem() = default;
    };
}
#endif