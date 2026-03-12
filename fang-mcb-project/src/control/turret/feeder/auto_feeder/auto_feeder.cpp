#include "auto_feeder.hpp"

#include "wrap/units/units_alias.hpp"

namespace fang::turret
{
    AutoFeeder::AutoFeeder
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

    void AutoFeeder::feedOn()
    {
        switch (state_)
        {
            case State::idle :
                feedMotor_->setTargetSpeed(feedRateToRPM());
                state_ = State::firing;
                break;

            case State::firing:
                break;
            case State::unjamming :
                // Do nothing.
                break;
        }
    }

    void AutoFeeder::feedOff()
    {
        feedMotor_->setTargetSpeed(kStillSpeed_);
    }

    void AutoFeeder::unjamOn()
    {
        feedMotor_->setTargetSpeed(-kUnjamSpeed_);
    }

    void AutoFeeder::unjamOff()
    {
        feedOff();
    }

    void AutoFeeder::update()
    {
        feedMotor_->update();

        switch (state_)
        {
            case State::idle :
                break;
            case State::firing:
                break;
            case State::unjamming :

                // Do nothing.
                break;
        }
       
    }

    void AutoFeeder::refresh() 
    {
        update();
    }

    void AutoFeeder::initialize()
    {
        feedMotor_->initialize();
    }

    RPM AutoFeeder::feedRateToRPM()
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