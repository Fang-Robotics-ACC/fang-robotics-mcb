#include "pierce.hpp"
#include "driver/drivers.hpp"
#include "modm/platform/core/delay_impl.hpp"


namespace fang::robot 
{
    using namespace units::literals;
    Pierce::Pierce(Drivers& drivers, const Config& config)
        :
            gimbal_{std::make_unique<turret::PierceFieldGimbal>(drivers, config.subsystemConfig.gimbalConfig)},
            feeder_{std::make_unique<turret::M2006SimpleFeeder>(drivers, config.subsystemConfig.feederConfig)},
            booster_{std::make_unique<turret::PierceAmmoBooster>(drivers, config.subsystemConfig.boosterConfig)},
            mecanumDrive_{std::make_unique<chassis::PierceMecanumDrive>(drivers, config.subsystemConfig.chassisConfig)},
            commandPack_{drivers, *booster_, *feeder_, *gimbal_, *mecanumDrive_, config.commandPackConfig}
    {
    }
    
    void Pierce::initialize()
    {
        initializeSubsystems();
        initializeCommands();
    }
    
    void Pierce::initializeSubsystems()
    {
        feeder_->registerAndInitialize();
        booster_->registerAndInitialize();
        gimbal_->registerAndInitialize();
        mecanumDrive_->registerAndInitialize();
    }

    void Pierce::initializeCommands()
    {
        commandPack_.initialize();
    }
}