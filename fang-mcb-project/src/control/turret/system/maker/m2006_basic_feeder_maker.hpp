#ifndef FANG_ROBOTICS_MCB_CONTROL_TURRET_SYSTEM_MAKER_M2006_BASIC_FEEDER_MAKER_HPP
#define FANG_ROBOTICS_MCB_CONTROL_TURRET_SYSTEM_MAKER_M2006_BASIC_FEEDER_MAKER_HPP
#include "control/turret/system/blueprint/basic_feeder_system.hpp"
#include "drivers.hpp"
#include "trap/motor/dji_m2006.hpp"

namespace control::turret
{
    /**
     * Gives a basic feeder that utilizes an M2006 motor
     */
    class M2006BasicFeederMaker
    {
    public:
        using FeedMotor = trap::motor::DjiM2006;
        struct Config
        {
            FeedMotor::Config         feedMotorConfig;
            BasicFeederSystem::Config   feederConfig;
        };

        M2006BasicFeederMaker(Drivers& drivers, const Config& config);
        BasicFeederSystem& getBasicFeeder();

    private:
        FeedMotor feedMotor_;
        BasicFeederSystem feeder_; 
    };
}
#endif