#pragma once


#include "driver/drivers.hpp"
//Subsystems
#include "custom_variant/subsystem/slice_mecanum_drive.hpp"
#include "custom_variant/subsystem/slice_field_gimbal.hpp"
#include "custom_variant/subsystem/slice_ammo_booster.hpp"
#include "cool_serial/byte_queue.hpp"

#include "control/turret/feeder/simple_feeder/m2006_simple_feeder.hpp"

#include "custom_variant/slice_command_pack.hpp"

#include "robot/base_robot.hpp"

#include "tap/communication/serial/remote.hpp"
#include "control/turret/input/fly_sky_gimbal_input.hpp"
#include "driver/remote/fly_sky.hpp"

namespace fang::robot
{
    /**
     * First Fang: Pierce
     * The first robot in Fang Robotics est. 2025
     */
    class Slice : public BaseRobot
    {
    public:
        using RemoteState = tap::control::RemoteMapState;

        struct InputConfig
        {
            chassis::DjiHolonomicInput::Config holonomic;
            turret::DjiGimbalInput::Config gimbal;
        };

        struct SubsystemConfig
        {
            chassis::SliceMecanumDrive::Config chassisConfig;
            turret::SliceFieldGimbal::Config gimbalConfig;
            fang::turret::M2006SimpleFeeder::Config feederConfig;
            turret::SliceAmmoBooster::Config boosterConfig;
        };

        struct Config
        {
            SubsystemConfig subsystemConfig;
            InputConfig input;
            command::SliceCommandPack::Config commandPackConfig;
        };

        Slice(Drivers& drivers, const Config& config)
            :
            uart_{drivers.uart},
            remote_{drivers.remote},
            flySkyByteQueue_{},
            flyRemote_{drivers.commandMapper, flySkyByteQueue_},
            holonomicInput_{drivers.remote, config.input.holonomic},
            gimbalInput_{drivers.remote, config.input.gimbal},
            flySkyGimbalInput_{flyRemote_, {remote::FlySky::Channel::leftVertical, remote::FlySky::Channel::leftHorizontal}},
            BaseRobot{makeRobot(drivers, holonomicInput_, gimbalInput_, config)}
        {}

        void initialize() override
        {
            BaseRobot::initialize();
            uart_.init<tap::communication::serial::Uart::Uart1, 115200, tap::communication::serial::Uart::Parity::Disabled>();
            remote_.initialize();
        }

        void update() override
        {
            uint8_t data{};
            while(uart_.read(tap::communication::serial::Uart::Uart1,  &data))
            {
                flySkyByteQueue_.push(data);
            }
            remote_.read();
            flyRemote_.update();
        }

    private:
        tap::communication::serial::Uart& uart_;
        tap::communication::serial::Remote& remote_;
        coolSerial::ByteQueue flySkyByteQueue_;
        remote::FlySky flyRemote_;
        chassis::DjiHolonomicInput holonomicInput_;
        turret::DjiGimbalInput gimbalInput_;
        turret::FlySkyGimbalInput flySkyGimbalInput_;


        static BaseRobot makeRobot(Drivers& drivers, chassis::IHolonomicInput& holonomicInput, turret::IGimbalInput& gimbalInput, const Config& config)
        {
            auto gimbal{std::make_unique<turret::SliceFieldGimbal>(drivers, config.subsystemConfig.gimbalConfig)};
            auto feeder{std::make_unique<turret::M2006SimpleFeeder>(drivers, config.subsystemConfig.feederConfig)};
            auto booster{std::make_unique<turret::SliceAmmoBooster>(drivers, config.subsystemConfig.boosterConfig)};
            auto mecanumDrive{std::make_unique<chassis::SliceMecanumDrive>(drivers, config.subsystemConfig.chassisConfig)};
            auto commandPack
            {
                std::make_unique<command::SliceCommandPack>
                (
                    drivers,
                    *booster,
                    *feeder,
                    *gimbal,
                    *mecanumDrive,
                    gimbalInput,
                    holonomicInput,
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
