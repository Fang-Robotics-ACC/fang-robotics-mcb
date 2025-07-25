#ifndef FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SUBSYSTEM_M2006_SIMPLE_FEEDER_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SUBSYSTEM_M2006_SIMPLE_FEEDER_SUBSYSTEM_HPP
#include "simple_feeder_subsystem.hpp"
#include "driver/drivers.hpp"
#include "control/turret/feeder/simple_feeder_system/simple_feeder_system.hpp"
#include "control/turret/feeder/simple_feeder_system/m2006_simple_feeder_factory.hpp"

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
        using SimpleFeederSubsystemPtr = std::unique_ptr<SimpleFeederSubsystem>;
        struct Config
        {
            FeedMotor::Config         feedMotorConfig;
            SimpleFeederSubsystem::Config   feederSubsystemConfig;
            SimpleFeederSystem::Config feederSystemConfig;
        };

        M2006SimpleFeederSubsystem(Drivers& drivers, const Config& config);
        static SimpleFeederSubsystemPtr makeUnique(Drivers& drivers, const Config& config);

    };
}
#endif