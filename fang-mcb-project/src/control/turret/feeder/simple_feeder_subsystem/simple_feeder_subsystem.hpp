#ifndef FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SUBSYSTEM_SIMPLE_FEEDER_SUBSYTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SUBSYSTEM_SIMPLE_FEEDER_SUBSYTEM_HPP
#include "tap/control/subsystem.hpp"
#include "driver/drivers.hpp"
#include "control/turret/util/heat_limiter.hpp"
#include "wrap/rail/rail_turret_aliases.hpp"

namespace fang::turret
{
    class SimpleFeederSubsystem :
        virtual public ISimpleFeederSubsystemControl,
        virtual public tap::control::Subsystem
    {
    public:
        using HeatLimiter = turret::HeatLimiter;
        struct Config
        {
            HeatLimiter::Config heatLimiterConfig;
        };

        SimpleFeederSubsystem(Drivers& drivers, ISimpleFeederPtr feeder, const Config& config);

        void initialize() override;
        void refresh() override;

        void refreshSafeDisconnect() override;

        void feedOn() override;
        void feedOff() override;

        void unjamOn() override;
        void unjamOff() override;

    private:
        ISimpleFeederPtr feeder_;
        HeatLimiter  heatLimiter_;
    };
}
#endif