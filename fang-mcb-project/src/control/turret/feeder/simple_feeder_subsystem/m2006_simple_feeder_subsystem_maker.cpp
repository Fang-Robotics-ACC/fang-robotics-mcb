#include "m2006_simple_feeder_subsystem_maker.hpp"
namespace fang::turret
{
    M2006SimpleFeederSubsystemMaker::SimpleFeederSubsystemPtr M2006SimpleFeederSubsystemMaker::Make(Drivers& drivers, const Config& config)
    {
        auto feederSystem{M2006SimpleFeederFactory::Make(drivers, {config.feedMotorConfig, config.feederSystemConfig})};
        return std::make_unique<SimpleFeederSubsystem>(drivers, std::move(feederSystem), config.feederSubsystemConfig);
    }
}