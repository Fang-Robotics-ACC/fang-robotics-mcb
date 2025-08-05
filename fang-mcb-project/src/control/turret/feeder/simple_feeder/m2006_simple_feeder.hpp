#pragma once

#include "simple_feeder.hpp"
#include "driver/drivers.hpp"
#include "wrap/trap/motor/dji_m2006.hpp"

namespace fang::turret
{
    /**
     * Gives a basic feeder that utilizes an M2006 motor
     */
    class M2006SimpleFeeder : public SimpleFeeder
    {
    public:
        using FeedMotor = trap::motor::DjiM2006;
        struct Config
        {
            FeedMotor::Config         feedMotorConfig;
            SimpleFeeder::Config   feederConfig;
        };

        M2006SimpleFeeder(Drivers& drivers, const Config& config):
            SimpleFeeder
            (
                drivers,
                std::make_unique<FeedMotor>(drivers, config.feedMotorConfig),
                config.feederConfig
            )
        {}

    };
}