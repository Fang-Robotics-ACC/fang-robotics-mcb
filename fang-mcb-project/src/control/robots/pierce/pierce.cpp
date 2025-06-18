#include "pierce.hpp"
#include "drivers.hpp"
#include "configuration/motion_control_config.hpp"


namespace control
{
    using namespace units::literals;
    Pierce::Pierce(Drivers& drivers, const Config& config)
        :
            m_drivers{drivers},
            mk_subsystemConfig{config.subsystemConfig},
            mk_inputConfig{config.inputConfig},
            mk_commandConfig{config.commandConfig},
            m_imu{drivers.bmi088},
            m_chassis{drivers, mk_subsystemConfig.chassisConfig},
            m_gimbal{drivers, m_imu, mk_subsystemConfig.gimbalConfig},
            m_feeder{drivers, mk_subsystemConfig.feederConfig},
            m_booster{drivers, mk_subsystemConfig.boosterConfig},
            m_chassisInput{drivers.remote, mk_inputConfig.chassisInputConfig},
            m_turretInput{drivers.remote, mk_inputConfig.turretInputConfig}
    {
    }
    
    void Pierce::initialize()
    {
        initializeSubsystems();
        setDefaultCommands();
        registerIoMappings();
    }
    
    void Pierce::initializeSubsystems()
    {
        m_feeder.registerAndInitialize();
        m_booster.registerAndInitialize();
        m_gimbal.registerAndInitialize();

        m_chassis.registerAndInitialize();
    }
    
    
    void Pierce::setDefaultCommands()
    {
        m_gimbal.setDefaultCommand(&m_aimCommnd);
    }
    
    void Pierce::registerIoMappings()
    {
        m_drivers.commandMapper.addMap(&m_activateBoosterCommandMapping);
        m_drivers.commandMapper.addMap(&m_activateAutofireCommandMapping);
        m_drivers.commandMapper.addMap(&m_shurikenCommandMapping);
        m_drivers.commandMapper.addMap(&m_fieldMecanumCommandMapping);
    }
}