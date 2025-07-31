#ifndef FANG_ROBOTICS_MCB_CONTROL_CASSIS_DRIVE_QUAD_DRIVE_QUAD_DRIVE_SUBSYSTEM_REPEAT_ULTRA_MK2_QUAD_DRIFVE_SUBSYSTE_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CASSIS_DRIVE_QUAD_DRIVE_QUAD_DRIVE_SUBSYSTEM_REPEAT_ULTRA_MK2_QUAD_DRIFVE_SUBSYSTE_HPP
#include "base_quad_drive.hpp"
#include "driver/motor/repeat_robotics/gearbox_repeat_ultra_mk2.hpp"

#include <memory>
namespace fang::chassis
{
    class RepeatUltraMk2QuadDriveSubsystem : public BaseQuadDrive
    {
    public:
        using Motor = motor::GearboxRepeatUltraMk2;
        struct Config
        {
            Motor::Config frontLeftConfig;
            Motor::Config frontRightConfig;
            Motor::Config rearLeftConfig;
            Motor::Config rearRightConig;
        };

        RepeatUltraMk2QuadDriveSubsystem(Drivers& drivers, const Config& config):
            BaseQuadDrive
            {
                drivers,
                std::make_unique<Motor>(config.frontLeftConfig),
                std::make_unique<Motor>(config.frontRightConfig),
                std::make_unique<Motor>(config.rearLeftConfig),
                std::make_unique<Motor>(config.rearRightConig)
            }
        {
        }
    };
}
#endif