#ifndef FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SYSTEM_SIMPLE_FEEDER_SYSTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SYSTEM_SIMPLE_FEEDER_SYSTEM_HPP
#include "driver/drivers.hpp"

#include "wrap/rail/rail_turret_aliases.hpp"
#include "wrap/rail/rail_motor_owner.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::turret
{   
    /**
     * Intermediate dependency injection based class using the deprecated feeder api
     */
    class SimpleFeederSystem : virtual public ISimpleFeeder
    {
    public:
        using Motor = motor::ISpeedMotorPtr;
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
        SimpleFeederSystem(Motor feedMotor, const Config& config);

        void feedOn() override;
        void feedOff() override;

        void unjamOn() override;
        void unjamOff() override;

        /**
         * Check if the feed system is feeding ammo or not.
         */
        bool getActiveStatus();

        void initialize() override;
        void update() override;
    private:
        RPM feedRateToRPM();

        static constexpr RPM kStillSpeed_{0.0};

        Motor feedMotor_;
        const int kRoundsPerRevolution_;
        const Hertz kFeedRate_;
        const RPM kUnjamSpeed_;

        bool activeStatus_{false};

    };  
}
#endif