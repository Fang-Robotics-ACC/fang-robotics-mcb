#ifndef FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SUBSYSTEM_M2006_SIMPLE_FEEDER_SUBSYSTEM_MAKER_HPP
#define FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SUBSYSTEM_M2006_SIMPLE_FEEDER_SUBSYSTEM_MAKER_HPP
#include "simple_feeder_subsystem.hpp"
#include "drivers.hpp"
#include "turret/feeder/simple_feeder_system/simple_feeder_system.hpp"
#include "turret/feeder/simple_feeder_system/m2006_simple_feeder_maker.hpp"

#include "trap/motor/dji_m2006.hpp"

namespace control::turret
{
    /**
     * Gives a basic feeder that utilizes an M2006 motor
     */
    class M2006SimpleFeederSubsystemMaker
    {
    public:
        using FeedMotor = trap::motor::DjiM2006;
        struct Config
        {
            FeedMotor::Config         feedMotorConfig;
            SimpleFeederSubsystem::Config   feederSubsystemConfig;
            SimpleFeederSystem::Config feederSystemConfig;
        };

        M2006SimpleFeederSubsystemMaker(Drivers& drivers, const Config& config);
        SimpleFeederSubsystem& getMade();

    private:
        M2006SimpleFeederMaker feederSystemMaker_;
        SimpleFeederSubsystem feederSubsystem_;
    };
}
#endif