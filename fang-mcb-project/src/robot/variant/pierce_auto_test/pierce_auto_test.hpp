#ifndef FANG_ROBOTICS_MCB_INFANTRY_HPP
#define FANG_ROBOTICS_MCB_INFANTRY_HPP
#include "driver/drivers.hpp"
//Subsystems
#include "robot/variant/pierce/custom_variant/subsystem/pierce_mecanum_drive.hpp"
#include "robot/variant/pierce/custom_variant/subsystem/pierce_field_gimbal.hpp"
#include "robot/variant/pierce/custom_variant/subsystem/pierce_ammo_booster.hpp"

#include "control/turret/feeder/simple_feeder/m2006_simple_feeder.hpp"
#include "control/command/pierce_auto_test_command_pack.hpp"

#include "robot/base_robot.hpp"
// Auto tests
#include "control/turret/basic_proxy_turret_input_updater.hpp"
#include "control/turret/proxy_turret_input.hpp"

namespace fang::robot
{
    /**
     * First Fang: Pierce
     * The first robot in Fang Robotics est. 2025
     */
    class PierceAutoTest : public BaseRobot
    {
    public:
        using RemoteState = tap::control::RemoteMapState;
        struct SubsystemConfig
        {
            chassis::PierceMecanumDrive::Config chassisConfig;
            turret::PierceFieldGimbal::Config gimbalConfig;
            fang::turret::M2006SimpleFeeder::Config feederConfig;
            turret::PierceAmmoBooster::Config boosterConfig;
        };

        struct Config
        {
            SubsystemConfig subsystemConfig;
            command::PierceAutoTestCommandPack::Config commandPackConfig;
        };

        PierceAutoTest(Drivers& drivers, const Config& config)
            :
            BaseRobot{makeRobot(drivers, config)},
            drivers_{drivers}
        {
        }

        void update()
        {
            proxyTurretInputUpdater_.update();
        }

    private:
        Drivers& drivers_;
        turret::ProxyTurretInput proxyTurretInput_{{1.0, 1.0}}; // Don't scale
        turret::BasicProxyTurretInputUpdater proxyTurretInputUpdater_{proxyTurretInput_, drivers_.jankyFloatHandler};
        BaseRobot makeRobot(Drivers& drivers, const Config& config)
        {
            auto gimbal{std::make_unique<turret::PierceFieldGimbal>(drivers, config.subsystemConfig.gimbalConfig)};
            auto feeder{std::make_unique<turret::M2006SimpleFeeder>(drivers, config.subsystemConfig.feederConfig)};
            auto booster{std::make_unique<turret::PierceAmmoBooster>(drivers, config.subsystemConfig.boosterConfig)};
            auto mecanumDrive{std::make_unique<chassis::PierceMecanumDrive>(drivers, config.subsystemConfig.chassisConfig)};
            auto commandPack
            {
                std::make_unique<command::PierceAutoTestCommandPack>
                (
                    drivers,
                    proxyTurretInput_,
                    *booster,
                    *feeder,
                    *gimbal,
                    *mecanumDrive,
                    config.commandPackConfig
                )
            };
            // If I could get the makeUniqueVector thing to work, this might be more worthwhile...
            Subsystems subsystems{};
            subsystems.push_back(std::move(booster));
            subsystems.push_back(std::move(feeder));
            subsystems.push_back(std::move(gimbal));
            subsystems.push_back(std::move(mecanumDrive));

            CommandPacks commandPacks{};
            commandPacks.push_back(std::move(commandPack));
            return BaseRobot{drivers.commandScheduler, std::move(subsystems), std::move(commandPacks)};
        }
    };
}
#endif