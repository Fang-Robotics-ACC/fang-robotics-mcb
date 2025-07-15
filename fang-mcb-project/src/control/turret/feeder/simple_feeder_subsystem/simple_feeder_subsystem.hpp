#ifndef FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SUBSYSTEM_SIMPLE_FEEDER_SUBSYTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SUBSYSTEM_SIMPLE_FEEDER_SUBSYTEM_HPP
#include "drivers.hpp"
#include "control/turret/util/heat_limiter.hpp"
#include "rail/turret/feeder/isimple_feeder.hpp"
#include "wrap/rail/rail_turret_aliases.hpp"

#include "tap/control/subsystem.hpp"

namespace control::turret
{
    class SimpleFeederSubsystem:
        virtual public tap::control::Subsystem,
        virtual public ISimpleFeeder,
        virtual public ISimpleFeederSubsystemControl
    {
    public:
        using HeatLimiter = control::turret::HeatLimiter;
        struct Config
        {
            HeatLimiter::Config heatLimiterConfig;
        };

        SimpleFeederSubsystem(Drivers& drivers, ISimpleFeeder& feeder ,const Config& config);

        void initialize() override;
        void update() override;
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