#ifndef FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSI_I_QUAD_DRIVE_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSI_I_QUAD_DRIVE_SUBSYSTEM_HPP

#include "wrap/rail/chassis/iquad_control.hpp"
#include "tap/control/subsystem.hpp"

namespace fang::chassis
{
    class IQuadDriveSubsystem:
        virtual public IQuadControl,
        virtual public tap::control::Subsystem
    {
    public:
        virtual ~IQuadDriveSubsystem() {};
    };
}
#endif