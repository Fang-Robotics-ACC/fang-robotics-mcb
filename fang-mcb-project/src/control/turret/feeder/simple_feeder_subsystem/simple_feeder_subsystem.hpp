#ifndef FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SUBSYSTEM_SIMPLE_FEEDER_SUBSYTEM_HPP
#define FANG_ROBOTICS_MCB_CONTROL_TURRET_FEEDER_SIMPLE_FEEDER_SUBSYSTEM_SIMPLE_FEEDER_SUBSYTEM_HPP
#include "control/turret/util/heat_limiter.hpp"
#include "driver/drivers.hpp"

#include "wrap/rail/turret/isimple_feeder_subsystem.hpp"
#include "wrap/rail/turret/isimple_feeder.hpp"

#include "tap/control/subsystem.hpp"

#include <memory>

namespace fang::turret
{
    class SimpleFeederSubsystem : public ISimpleFeederSubsystem
    {
    public:
        using HeatLimiter = turret::HeatLimiter;
        struct Config
        {
            HeatLimiter::Config heatLimiterConfig;
        };

        SimpleFeederSubsystem(Drivers& drivers, std::unique_ptr<ISimpleFeeder> feeder, const Config& config);

        void initialize() override;
        void refresh() override;

        void refreshSafeDisconnect() override;

        void feedOn() override;
        void feedOff() override;

        void unjamOn() override;
        void unjamOff() override;

    private:
        std::unique_ptr<ISimpleFeeder> feeder_;
        HeatLimiter  heatLimiter_;
    };
}
#endif