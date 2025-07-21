#include "m2006_simple_feeder_subsystem_maker.hpp"
namespace fang::turret
{

    M2006SimpleFeederSubsystemMaker::M2006SimpleFeederSubsystemMaker(Drivers& drivers, const Config& config):
        feederSystemMaker_{drivers, {config.feedMotorConfig, config.feederSystemConfig}},
        feederSubsystem_{drivers, feederSystemMaker_.getMade(), config.feederSubsystemConfig}
    {
    }

    SimpleFeederSubsystem& M2006SimpleFeederSubsystemMaker::getMade()
    {
        return feederSubsystem_;
    }
}