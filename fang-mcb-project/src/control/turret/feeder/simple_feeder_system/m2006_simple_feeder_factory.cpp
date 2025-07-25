#include "m2006_simple_feeder_factory.hpp"

namespace fang::turret
{
    std::unique_ptr<SimpleFeederSystem> M2006SimpleFeeder::makeUnique(Drivers& drivers, const Config& config)
    {
        auto feedMotor{std::make_unique<FeedMotor>(drivers, config.feedMotorConfig)};
        return std::make_unique<SimpleFeederSystem>(std::move(feedMotor), config.feederConfig);
    }
}