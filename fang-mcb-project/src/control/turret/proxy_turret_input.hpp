#pragma once

#include "wrap/rail/turret/iturret_input_handler.hpp"

namespace fang::turret
{
    /**
     * This is designed to be a node for testing of various autonomous services.
     * 
     * For example: TurretMessageHandler -> sets pitch
     * AimCommand <-- gets pitch from ProxyTurretInput
     */
    class ProxyTurretInput : public ITurretInputHandler 
    {
    public:
        /**
         * @param pitchScale = how much the pitch is multiplied by
         * @param yawScale = how much the yaw is multiplied by
         */
        struct Config
        {
            double pitchScale;
            double yawScale;
        };

        ProxyTurretInput(const Config& config);

        void setPitch(double pitch);
        double getPitch() const override;

        /**
         * Counterclockwise is positive, clockwise is negative
         * (Math convention.)
         */
        void setYaw(double yaw);

        /**
         * Counterclockwise is positive, clockwise is negative
         * (Math convention.)
         */
        double getYaw() const override;
    private:
        const Config kConfig_;

        double pitch_{};
        double yaw_{};
    };
}