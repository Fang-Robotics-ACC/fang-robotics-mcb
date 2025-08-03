#include "simple_feeder.hpp"

#include "wrap/units/units_alias.hpp"

namespace fang::turret
{
    SimpleFeeder::SimpleFeeder
    (
        Drivers& drivers,
        std::unique_ptr<Motor> feedMotor,
        const Config& config
    ):
        SimpleFeederSubsystem(drivers),
        feedMotor_{std::move(feedMotor)},
        kRoundsPerRevolution_{config.roundsPerRevolution},
        kFeedRate_{config.feedRate},
        kUnjamSpeed_{config.unjamSpeed},
        heatLimiter_{drivers.refSerial, config.heatLimiterConfig}
    {
    }

    void SimpleFeeder::feedOn()
    {
        feedMotor_->setTargetSpeed(feedRateToRPM());
    }

    void SimpleFeeder::feedOff()
    {
        feedMotor_->setTargetSpeed(kStillSpeed_);
    }

    void SimpleFeeder::unjamOn()
    {
        feedMotor_->setTargetSpeed(-kUnjamSpeed_);
    }

    void SimpleFeeder::unjamOff()
    {
        feedOff();
    }

    void SimpleFeeder::update()
    {
        feedMotor_->update();
    }

    void SimpleFeeder::initialize()
    {
        feedMotor_->initialize();
    }

    RPM SimpleFeeder::feedRateToRPM()
    {
        //If there are two rounds per revolution,
        //The wheel only needs to rotate half as fast
        //to meet the specified feedRate
        const Hertz revolutionFrequency{kFeedRate_ / kRoundsPerRevolution_};
        //Slightly risky use to convert to preoper unit. It is not too risky since
        //We are simply converting from the frequency into how often revolutions happen.
        //This gets implicitly converted into RPM :)
        const units::angular_velocity::revolutions_per_second_t revolutionsPerSecond {revolutionFrequency.to<double>()};
        return revolutionsPerSecond;
    }   
}