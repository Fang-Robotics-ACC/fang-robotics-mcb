#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_QUAD_DRIVE_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_QUAD_DRIVE_SUBSYSTEM_HPP

#include "wrap/rail/chassis/iquad_drive.hpp"
#include "tap/control/subsystem.hpp"

namespace fang::chassis
{
    class QuadDriveSubsystem:
        virtual public IQuadDrive,
        public tap::control::Subsystem
    {
    public:
        QuadDriveSubsystem(tap::Drivers& drivers):
            Subsystem{&drivers}
        {}

        virtual ~QuadDriveSubsystem() = default;
    };
}
#endif