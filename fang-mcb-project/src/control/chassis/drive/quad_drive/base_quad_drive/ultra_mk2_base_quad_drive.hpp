#ifndef FANG_ROBOTICS_MCB_CONTROL_CASSIS_DRIVE_QUAD_DRIVE_ULTRA_MK2_BASE_QUAD_DRIVE_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CASSIS_DRIVE_QUAD_DRIVE_ULTRA_MK2_BASE_QUAD_DRIVE_HPP
#include "base_quad_drive.hpp"
#include "driver/motor/repeat_robotics/gearbox_repeat_ultra_mk2.hpp"

#include <memory>
namespace fang::chassis
{
    class UltraMk2BaseQuaddrive : public BaseQuadDrive
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

        UltraMk2BaseQuaddrive(Drivers& drivers, const Config& config):
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