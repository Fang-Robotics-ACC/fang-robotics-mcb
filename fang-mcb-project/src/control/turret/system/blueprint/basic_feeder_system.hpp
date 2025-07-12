#ifndef FANG_ROBOTICS_MCB_CONTROL_TURRET_SYSTEM_BLUEPRINT_BASIC_FEEDER_SYSTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_TURRET_SYSTEM_BLUEPRINT_BASIC_FEEDER_SYSTEM_HPP
#include "unitaliases.hpp"
#include "wrap/rail/rail_motors.hpp"

#include "drivers.hpp"

namespace control::turret
{   
    /**
     * Intermediate dependency injection based class using the deprecated feeder api
     */
    class BasicFeederSystem
    {
    public:
        /**
         * roundsPerRevolution cannot be negative or zero which would cause corruption.
         * feedRate - this is the starting rounds per second
         * motorConfig - this is the configuration of the feeder motor
         */
        struct Config
        {
            int roundsPerRevolution;
            Hertz feedRate;
            RPM unjamSpeed;
        };

        /**
         * A positive value sent to the feedMotor means that it will feed.
         */
        BasicFeederSystem(motor::ISpeedMotor &feedMotor, const Config& config);

        void feedOn();
        void feedOff();

        void unjamOn();
        void unjamOff();

        /**
         * Check if the feed system is feeding ammo or not.
         */
        bool getActiveStatus();

        void update();
        void initialize();
    private:
        RPM feedRateToRPM();

        static constexpr RPM kStillSpeed_{0.0};

        const int kRoundsPerRevolution_;
        const Hertz kFeedRate_;
        const RPM kUnjamSpeed_;

        bool activeStatus_{false};

        motor::ISpeedMotor& feedMotor_;
    };  
}
#endif