#include "m2006_simple_feeder_subsystem.hpp"
namespace fang::turret
{
    std::unique_ptr<SimpleFeederSubsystem> M2006SimpleFeederSubsystem::makeUnique(Drivers& drivers, const Config& config)
    {
        auto feederSystem{M2006SimpleFeeder::makeUnique(drivers, {config.feedMotorConfig, config.feederSystemConfig})};
        return std::make_unique<SimpleFeederSubsystem>(drivers, std::move(feederSystem), config.feederSubsystemConfig);
    }
}