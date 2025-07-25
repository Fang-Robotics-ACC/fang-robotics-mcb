#ifndef FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_M2006_SIMPLE_FEEDER_MAKER_HPP
#define FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_M2006_SIMPLE_FEEDER_MAKER_HPP
#include "simple_feeder_system.hpp"
#include "driver/drivers.hpp"
#include "wrap/trap/motor/dji_m2006.hpp"

namespace fang::turret
{
    /**
     * Gives a basic feeder that utilizes an M2006 motor
     */
    class M2006SimpleFeederFactory
    {
    public:
        using FeedMotor = trap::motor::DjiM2006;
        struct Config
        {
            FeedMotor::Config         feedMotorConfig;
            SimpleFeederSystem::Config   feederConfig;
        };

        static std::unique_ptr<SimpleFeederSystem> Make(Drivers& drivers, const Config& config);
    };
}
#endif