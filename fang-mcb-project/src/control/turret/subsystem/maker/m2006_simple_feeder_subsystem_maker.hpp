#ifndef FANG_ROBOTICS_MCB_CONTROL_TURRET_SUBSYSTEM_MAKER_M2006_SIMPLE_FEEDER_SUBSYSTEM_MAKER_HPP
#define FANG_ROBOTICS_MCB_CONTROL_TURRET_SUBSYSTEM_MAKER_M2006_SIMPLE_FEEDER_SUBSYSTEM_MAKER_HPP
#include "control/turret/subsystem/blueprint/simple_feeder_subsystem.hpp"
#include "drivers.hpp"
#include "trap/motor/dji_m2006.hpp"

namespace control::turret
{
    /**
     * Gives a basic feeder that utilizes an M2006 motor
     */
    class M2006SimpleFeederMaker
    {
    public:
        using FeedMotor = trap::motor::DjiM2006;
        struct Config
        {
            FeedMotor::Config         feedMotorConfig;
            SimpleFeederSubsystem::Config   feederConfig;
        };

        M2006SimpleFeederMaker(Drivers& drivers, const Config& config);
        SimpleFeederSubsystem& getMade();

    private:
        FeedMotor feedMotor_;
        SimpleFeederSubsystem feeder_;
    };
}
#endif