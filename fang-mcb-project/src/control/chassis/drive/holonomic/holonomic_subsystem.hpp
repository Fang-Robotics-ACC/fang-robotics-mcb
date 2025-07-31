#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_HOLONOMIC_HOLONOMIC_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_HOLONOMIC_HOLONOMIC_SUBSYSTEM_HPP
#include "driver/drivers.hpp"
#include "wrap/rail/chassis/iholonomic_drive.hpp"
#include "tap/control/subsystem.hpp"

namespace fang::chassis
{
    class HolonomicSubsystem:
        public IHolonomicDrive,
        public tap::control::Subsystem
    {
    public:
        HolonomicSubsystem(Drivers& drivers) : Subsystem{&drivers}
        {}
        virtual ~HolonomicSubsystem() {};
    };
}
#endif