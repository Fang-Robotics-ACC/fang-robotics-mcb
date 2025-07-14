#include "simple_feeder_system.hpp"


#include "unitaliases.hpp"


using namespace units::literals;
namespace control::turret
{
    using namespace units::literals;

    SimpleFeederSystem::SimpleFeederSystem(motor::ISpeedMotor& feedMotor, const Config& config)
    :   kRoundsPerRevolution_{config.roundsPerRevolution},
        kFeedRate_{config.feedRate},
        kUnjamSpeed_{config.unjamSpeed},
        feedMotor_{feedMotor}
    {
        //assert(mk_roundsPerRevolution != 0 && "roundsPerRevolution must be zero");
        //assert(mk_roundsPerRevolution  > 0 && "roundsPerRevolution cannot be less than zero");
    }

    void SimpleFeederSystem::feedOn()
    {
        feedMotor_.setTargetSpeed(feedRateToRPM());
    }

    void SimpleFeederSystem::feedOff()
    {
        feedMotor_.setTargetSpeed(kStillSpeed_);
    }

    void SimpleFeederSystem::unjamOn()
    {
        feedMotor_.setTargetSpeed(-kUnjamSpeed_);
    }

    void SimpleFeederSystem::unjamOff()
    {
        feedOff();
    }

    void SimpleFeederSystem::update()
    {
        feedMotor_.update();
    }

    void SimpleFeederSystem::initialize()
    {
        feedMotor_.initialize();
    }

    RPM SimpleFeederSystem::feedRateToRPM()
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