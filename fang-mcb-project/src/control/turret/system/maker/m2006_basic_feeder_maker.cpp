#include "m2006_basic_feeder_maker.hpp"
namespace control::turret
{

    M2006BasicFeederMaker::M2006BasicFeederMaker(Drivers& drivers, const Config& config):
        feedMotor_{drivers, config.feedMotorConfig},
        feeder_{feedMotor_, config.feederConfig}
    {
    }

    BasicFeederSystem& M2006BasicFeederMaker::getBasicFeeder()
    {
        return feeder_;
    }
}