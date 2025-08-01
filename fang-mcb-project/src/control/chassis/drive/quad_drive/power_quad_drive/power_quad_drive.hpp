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
     * This provides control for a set of 4 ISpeedMotors
     * It manages the initialization and update functionality
     * as well.
     *
     * This is often passed into a holonomic drive or tank drive
     * to delegate managing the wheel speeds and updating each of the motors
     *
     * This can be managed by a taproot command (can be registered).
     */
    class PowerQuadDrive : public BaseQuadDrive
    {
    public:
        using Motor = motor::ISpeedMotor;

        PowerQuadDrive 
        (
            Drivers& drivers,
            std::unique_ptr<BaseQuadDrive> baseQuaddrive,
            std::unique_ptr<IPowerLimiterSystem> powerLimiter
        );

        virtual void setTargetWheelSpeeds(const QuadRPM& wheelSpeeds) override;
        virtual void initialize() override;
        virtual void update() override;
        virtual void refresh() override;
    private:
        std::unique_ptr<IPowerLimiterSystem> powerLimiter_;
    };
}