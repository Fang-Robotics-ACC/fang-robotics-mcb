#ifndef FANG_ROBOTICS_MCB_BASIC_FEEDER_SUBSYTEM_HPP
#define FANG_ROBOTICS_MCB_BASIC_FEEDER_SUBSYTEM_HPP
#include "drivers.hpp"
#include "control/turret/util/heat_limiter.hpp"
#include "rail/turret/feeder/isimple_feeder.hpp"
#include "wrap/rail/rail_turret_aliases.hpp"

#include "tap/control/subsystem.hpp"

namespace control::turret
{
    class BasicFeederSubsystem:
        virtual public tap::control::Subsystem,
        virtual public ISimpleFeeder
    {
    public:
        using HeatLimiter = control::turret::HeatLimiter;
        struct Config
        {
            HeatLimiter::Config heatLimiterConfig;
        };

        BasicFeederSubsystem(Drivers& drivers, ISimpleFeeder& feeder ,const Config& config);

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