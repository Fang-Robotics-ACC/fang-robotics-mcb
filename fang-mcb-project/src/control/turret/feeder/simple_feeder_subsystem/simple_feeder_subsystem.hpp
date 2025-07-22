#ifndef FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SUBSYSTEM_SIMPLE_FEEDER_SUBSYTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SUBSYSTEM_SIMPLE_FEEDER_SUBSYTEM_HPP
#include "tap/control/subsystem.hpp"
#include "drivers.hpp"
#include "control/turret/util/heat_limiter.hpp"
#include "wrap/rail/rail_turret_aliases.hpp"

namespace control::turret
{
    class SimpleFeederSubsystem :
        virtual public ISimpleFeederSubsystemControl,
        virtual public tap::control::Subsystem
    {
    public:
        using HeatLimiter = control::turret::HeatLimiter;
        struct Config
        {
            HeatLimiter::Config heatLimiterConfig;
        };

        SimpleFeederSubsystem(Drivers& drivers, ISimpleFeeder& feeder, const Config& config);

        void initialize() override;
        void refresh() override;

        void refreshSafeDisconnect() override;

        void feedOn() override;
        void feedOff() override;

        void unjamOn() override;
        void unjamOff() override;

    private:
        ISimpleFeeder& feeder_;
        HeatLimiter  heatLimiter_;
    };
}
#endif