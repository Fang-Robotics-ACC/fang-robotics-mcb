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
            m_chassis{drivers, mk_config.chassisConfig},
            m_feeder{drivers, mk_config.feederConfig},
            m_turret{drivers, m_imu, mk_config.turretConfig},
            m_imu{drivers.bmi088},
            m_chassisInput{drivers.remote, mk_config.chassisInputConfig},
            m_turretInput{drivers.remote, mk_config.turretInputConfig}
    {
    }
    
    void Pierce::initialize()
    {
        initializeSubsystems();
        //registerSubsystems();
        setDefaultCommands();
        registerIoMappings();
    }
    
    void Pierce::initializeSubsystems()
    {
        m_drivers.pwm.setTimerFrequency(tap::gpio::Pwm::TIMER1, config::chassis::k_chassisPwmFreq.to<double>());
        m_turret.registerAndInitialize();
        m_turret.setPitch(m_turret.getMinPitch());
        m_chassis.registerAndInitialize();
    }
    
    
    void Pierce::setDefaultCommands()
    {
        m_turret.setDefaultCommand(&m_aimCommnd);
    }
    
    void Pierce::registerIoMappings()
    {
        m_drivers.commandMapper.addMap(&m_activateBoosterCommandMapping);
        m_drivers.commandMapper.addMap(&m_deactivateBoosterCommandMapping);
        m_drivers.commandMapper.addMap(&m_activateAutofireCommandMapping);
        m_drivers.commandMapper.addMap(&m_stopAutofireCommandMapping);
        m_drivers.commandMapper.addMap(&m_shurikenCommandMapping);
        m_drivers.commandMapper.addMap(&m_fieldMecanumCommandMapping);
    }
}