#pragma once
#include "power_quad_drive.hpp"

#include "driver/drivers.hpp"

#include "src/wrap/trap/motor/dji_m3508_old.hpp"

#include "wrap/rail/chassis/ipower_limiter_system.hpp"

namespace fang::chassis
{
    class M3508PowerQuadDrive : public PowerQuadDrive
    {
    public:
        using Motor = trap::motor::DjiM3508Old;
        using Config = QuadCollection<Motor::Config>;

        /**
         * You can pass your custom power limiter into
         * this class!
         */
        M3508PowerQuadDrive
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