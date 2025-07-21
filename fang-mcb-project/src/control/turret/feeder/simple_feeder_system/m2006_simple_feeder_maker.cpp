#include "m2006_simple_feeder_maker.hpp"
namespace fang::turret
{

    M2006SimpleFeederMaker::M2006SimpleFeederMaker(Drivers& drivers, const Config& config):
        feedMotor_{drivers, config.feedMotorConfig},
        feeder_{feedMotor_, config.feederConfig}
    {
    }

    SimpleFeederSystem& M2006SimpleFeederMaker::getMade()
    {
        return feeder_;
    }
}