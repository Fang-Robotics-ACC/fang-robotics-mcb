#ifndef FANG_ROBOTICS_MCB_INFANTRY_HPP
#define FANG_ROBOTICS_MCB_INFANTRY_HPP
#include "driver/drivers.hpp"
//Subsystems
#include "custom_variant/subsystem/pierce_mecanum_drive.hpp"

#include "custom_variant/subsystem/pierce_field_gimbal.hpp"
#include "control/turret/feeder/simple_feeder/m2006_simple_feeder.hpp"
#include "custom_variant/subsystem/pierce_ammo_booster.hpp"

#include "control/command/pierce_command_pack.hpp"

namespace fang::robot
{
    /**
     * First Fang: Pierce
     * The first robot in Fang Robotics est. 2025
     */
    class Pierce
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
            command::PierceCommandPack::Config commandPackConfig;
        };

        Pierce(Drivers& drivers, const Config& config);
        void initialize();
    private:
        static constexpr Milliseconds k_startupDelay{1500};

        void initializeSubsystems();
        void initializeCommands();

        std::unique_ptr<turret::PierceFieldGimbal> gimbal_;
        std::unique_ptr<fang::turret::SimpleFeeder> feeder_;
        std::unique_ptr<fang::turret::PierceAmmoBooster> booster_;
        std::unique_ptr<fang::chassis::PierceMecanumDrive> mecanumDrive_;

        command::PierceCommandPack commandPack_;

    };
}
#endif