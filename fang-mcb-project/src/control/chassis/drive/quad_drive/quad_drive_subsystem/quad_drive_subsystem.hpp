#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_QUAD_SUBSYSTEM_DRIVE_QUAD_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_DRIVE_QUAD_SUBSYSTEM_DRIVE_QUAD_SUBSYSTEM_HPP
#include "control/chassis/drive/quad_drive/data/quad_drive_data.hpp"
#include "wrap/rail/chassis/iquad_drive_subsystem.hpp"
#include "wrap/rail/rail_motor_owner.hpp"
namespace fang::chassis
{
    class QuadDriveSystem:
        virtual public IQuadDriveSubsystem
    {
    public:
        virtual void setTargetWheelSpeeds(const QuadRPM& wheelSpeeds) override;
        virtual void initialize() override;
        virtual void refresh() override;
    private:
    };
}
#endif