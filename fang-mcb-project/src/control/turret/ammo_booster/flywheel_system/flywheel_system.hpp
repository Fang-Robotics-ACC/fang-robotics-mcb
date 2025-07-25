#ifndef FANG_ROBOTICS_MCB_CONTROL_TURRET_SYSTEM_BLUEPRINT_FLYWHEEL_SYSTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_TURRET_SYSTEM_BLUEPRINT_FLYWHEEL_SYSTEM_HPP
#include "driver/drivers.hpp"

#include "wrap/rail/rail_motor_owner.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::turret
{
    /**
     * This is meant to abstract a single flywheel of a given radius.
     * It's update function must be periodically called in order for the
     * motor to be called. This is not a taproot subsystem, it is meant
     * to not be used by taproot's command scheduler. This is to provide
     * the turret subsystem a "subsubsystem", which is not supported by taproot.
     */
    class FlywheelSystem:
        virtual public motor::ISpeedWheel
    {
    public:
        using Motor = motor::ISpeedMotorPtr;
        struct Config
        {
            Meters radius;
        };

        FlywheelSystem(Motor motor, const Config& config);

		void setTargetRimSpeed(const MetersPerSecond& rimSpeed) override;

        void initialize() override;
        void update() override;
    private:
        RPM RimSpeedToMotorSpeed(const MetersPerSecond& rimSpeed) const;
        const MetersPerRadians kRadius_; //This is required for the math to smoothly work
        Motor motor_;

        MetersPerSecond targetRimSpeed_{};
    };
}
#endif