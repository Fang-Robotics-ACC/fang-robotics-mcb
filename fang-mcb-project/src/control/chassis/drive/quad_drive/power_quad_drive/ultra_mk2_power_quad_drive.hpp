#pragma once
#include "power_quad_drive.hpp"

#include "driver/drivers.hpp"
#include "driver/motor/repeat_robotics/ultra_mk2.hpp"

#include "wrap/rail/chassis/ipower_limiter_system.hpp"
namespace fang::chassis
{
    class UltraMk2PowerQuadDrive : public PowerQuadDrive
    {
    public:
        using Motor = motor::RepeatUltraMk2;
        using Config = QuadCollection<Motor::Config>;

        /**
         * You can pass your custom power limiter into
         * this class!
         */
        UltraMk2PowerQuadDrive
        (
            Drivers& drivers,
            std::unique_ptr<IPowerLimiterSystem> powerLimiter,
            const Config& config
        ):
            PowerQuadDrive
            {
                drivers,
                Motors
                {
                    std::make_unique<Motor>(drivers, config.frontLeft),
                    std::make_unique<Motor>(drivers, config.frontRight),
                    std::make_unique<Motor>(drivers, config.rearLeft),
                    std::make_unique<Motor>(drivers, config.rearRight)
                },
                std::move(powerLimiter)
            }
        {
        }
    };

}