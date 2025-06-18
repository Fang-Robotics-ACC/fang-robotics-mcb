#include "pierce.hpp"
#include "drivers.hpp"
#include "configuration/motion_control_config.hpp"
#include "control/robots/pierce/command_config/shuriken_config.hpp"


namespace control
{
    using namespace units::literals;
    Pierce::Pierce(Drivers& drivers)
        :
            m_drivers{drivers},
            m_imu{drivers.bmi088},
            m_chassis{drivers, mk_config.chassisConfig},
            m_gimbal{drivers, m_imu, mk_config.gimbalConfig},
            m_feeder{drivers, mk_config.feederConfig},
            m_booster{drivers, mk_config.boosterConfig},
            m_chassisInput{drivers.remote, mk_config.chassisInputConfig},
            m_turretInput{drivers.remote, mk_config.turretInputConfig}
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
        m_drivers.pwm.setTimerFrequency(tap::gpio::Pwm::TIMER1, config::chassis::k_chassisPwmFreq.to<double>());

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