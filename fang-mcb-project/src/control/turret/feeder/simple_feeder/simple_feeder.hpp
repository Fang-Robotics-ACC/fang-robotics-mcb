#pragma once

#include "driver/drivers.hpp"

#include "control/turret/feeder/simple_feeder_subsystem.hpp"
#include "control/turret/util/heat_limiter.hpp"
#include "wrap/rail/motor/ispeed_motor.hpp"
#include "wrap/units/units_alias.hpp"

namespace fang::turret
{   
    /**
     * Intermediate dependency injection based class using the deprecated feeder api
     */
    class SimpleFeeder : public SimpleFeederSubsystem 
    {
    public:
        using Motor = motor::ISpeedMotor;
        using HeatLimiter = fang::turret::HeatLimiter;
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
            HeatLimiter::Config heatLimiterConfig;
        };

        /**
         * A positive value sent to the feedMotor means that it will feed.
         */
        SimpleFeeder(Drivers& drivers, std::unique_ptr<Motor> feedMotor, const Config& config);

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

        std::unique_ptr<Motor> feedMotor_;
        const int kRoundsPerRevolution_;
        const Hertz kFeedRate_;
        const RPM kUnjamSpeed_;
        HeatLimiter  heatLimiter_;

        bool activeStatus_{false};

    };  
}