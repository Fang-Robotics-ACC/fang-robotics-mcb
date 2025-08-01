#pragma once
#include "control/chassis/drive/quad_drive/base_quad_drive/base_quad_drive.hpp"
#include "driver/drivers.hpp"
#include "wrap/rail/chassis/ipower_limiter_system.hpp"
#include "wrap/rail/rail_motor_owner.hpp"

#include <array>
#include <memory>

namespace fang::chassis
{
    /**
     * This checks the power useage and appropriately downscales it
     */
    class PowerQuadDrive : public BaseQuadDrive
    {
    public:

        PowerQuadDrive 
        (
            Drivers& drivers,
            Motors&& motors,
            std::unique_ptr<IPowerLimiterSystem> powerLimiter
        );

        virtual void setTargetWheelSpeeds(const QuadRPM& wheelSpeeds) override;
        virtual void initialize() override;
        virtual void update() override;
        virtual void refresh() override;

        virtual ~PowerQuadDrive() {}
    private:
        std::unique_ptr<IPowerLimiterSystem> powerLimiter_;
    };
}