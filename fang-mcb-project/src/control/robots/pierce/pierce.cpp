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
            m_chassisInput{drivers.remote, mk_config.chassisInputConfig},
            m_imu{drivers.bmi088},
            m_turret{drivers, m_imu, mk_config.turretConfig},
            m_aimCommnd{m_turret, drivers.inputHandler.getTurretInputs(), mk_config.turretMotionConfig},
            m_autofireCommand{m_turret},
            m_stopAutofireCommand{m_turret},
            m_activateBoosterCommand{m_turret},
            m_deactivateBoosterCommand{m_turret},
            m_chassis{drivers, config::chassis::k_defaultConfig},
            m_fieldMecanumCommand{m_chassis, m_turret, m_chassisInput, config::motion::k_defaultMotionConfig},
            m_shurikenCommand{m_chassis, m_turret, m_chassisInput, mk_shurikenConfig}
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
        //m_turret.boosterOn();//Hardcoded until command mapper bugs are solved
    }
    
    void Pierce::registerSubsystems()
    {
        //m_drivers.commandScheduler.registerSubsystem(&m_chassis);
    }
    
    void Pierce::setDefaultCommands()
    {
        m_turret.setDefaultCommand(&m_aimCommnd);
        //m_chassis.setDefaultCommand(&m_fieldMecanumCommand);
        //m_drivers.commandScheduler.addCommand(&m_activateBoosterCommand);
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