#include "feeder_system.hpp"


#include "unitaliases.hpp"


using namespace units::literals;
namespace control
{
    namespace turret
    {
        using namespace units::literals;

        FeederSystem::FeederSystem(Drivers& drivers, const Config& config)
        :   mk_roundsPerRevolution{config.roundsPerRevolution}, m_motor{drivers, config.motorConfig}
        {
            //assert(mk_roundsPerRevolution != 0 && "roundsPerRevolution must be zero");
            //assert(mk_roundsPerRevolution  > 0 && "roundsPerRevolution cannot be less than zero");
            setFeedRate(config.feedRate);
        }

        void FeederSystem::setFeedRate(const Hertz& feedRate)
        {
            //assert(feedRate >= 0_Hz && "Motor cannot be told to move backwards, this might cause damage");
            m_feedRate = feedRate;
        }

        void FeederSystem::feedOn()
        {
            m_motor.setTargetSpeed(feedRateToRPM());
        }

        void FeederSystem::feedOff()
        {
            m_motor.setTargetSpeed(mk_stillSpeed);
        }

        void FeederSystem::update()
        {
            m_motor.update();
        }

        void FeederSystem::initialize()
        {
            m_motor.initialize();
        }

        RPM FeederSystem::feedRateToRPM()
        {
            //If there are two rounds per revolution,
            //The wheel only needs to rotate half as fast
            //to meet the specified feedRate
            const Hertz revolutionFrequency{m_feedRate / mk_roundsPerRevolution};
            //Slightly risky use to convert to preoper unit. It is not too risky since
            //We are simply converting from the frequency into how often revolutions happen.
            //This gets implicitly converted into RPM :)
            const units::angular_velocity::revolutions_per_second_t revolutionsPerSecond {revolutionFrequency.to<double>()};
            return revolutionsPerSecond;
        }
    }
}