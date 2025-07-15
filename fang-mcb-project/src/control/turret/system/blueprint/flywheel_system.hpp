#ifndef FANG_ROBOTICS_MCB_CONTROL_TURRET_SYSTEM_BLUEPRINT_FLYWHEEL_SYSTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_TURRET_SYSTEM_BLUEPRINT_FLYWHEEL_SYSTEM_HPP
#include "unitaliases.hpp"
#include "wrap/rail/rail_motors.hpp"


#include "drivers.hpp"


namespace control
{
    namespace turret
    {
        /**
         * This is meant to abstract a single flywheel of a given radius.
         * It's update function must be periodically called in order for the
         * motor to be called. This is not a taproot subsystem, it is meant
         * to not be used by taproot's command scheduler. This is to provide
         * the turret subsystem a "subsubsystem", which is not supported by taproot.
         * 
         */
        class FlywheelSystem:
            virtual public motor::ISpeedWheel
        {
        public:
            using Motor = motor::ISpeedMotor;
            struct Config
            {
                Meters radius;
            };

            FlywheelSystem(Motor& motor, const Config& config);

            void setTargetRimSpeed(const MetersPerSecond& rimSpeed);
            MetersPerSecond getTargetRimSpeed() const override;

            void initialize() override;
            void update() override;
        private:
            RPM RimSpeedToMotorSpeed(const MetersPerSecond& rimSpeed) const;
            MetersPerRadians m_radius; //This is required for the math to smoothly work
            Motor& motor_;
        };
    }
}
#endif