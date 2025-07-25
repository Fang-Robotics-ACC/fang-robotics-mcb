#ifndef FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SUBSYSTEM_M2006_SIMPLE_FEEDER_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SUBSYSTEM_M2006_SIMPLE_FEEDER_SUBSYSTEM_HPP
#include "simple_feeder_subsystem.hpp"
#include "driver/drivers.hpp"
#include "control/turret/feeder/simple_feeder_system/simple_feeder_system.hpp"
#include "control/turret/feeder/simple_feeder_system/m2006_simple_feeder.hpp"

#include "wrap/trap/motor/dji_m2006.hpp"

namespace fang::turret
{
    /**
     * Gives a basic feeder that utilizes an M2006 motor
     */
    class M2006SimpleFeederSubsystem
    {
    public:
        using FeedMotor = trap::motor::DjiM2006;
        struct Config
        {
            FeedMotor::Config         feedMotorConfig;
            SimpleFeederSubsystem::Config   feederSubsystemConfig;
            SimpleFeederSystem::Config feederSystemConfig;
        };
        static std::unique_ptr<SimpleFeederSubsystem> makeUnique(Drivers& drivers, const Config& config);
    };
}
#endif