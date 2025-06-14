#include "pierce.hpp"
#include "drivers.hpp"
#include "configuration/motion_control_config.hpp"


namespace control
{
    using namespace units::literals;
    Pierce::Pierce(Drivers& drivers)
        :
            m_drivers{drivers},
            m_imu{drivers.bmi088},
            m_turret{drivers, m_imu, mk_config.turretConfig},
            m_aimCommnd{m_turret, drivers.inputHandler.getTurretInputs(), mk_config.turretMotionConfig},
            m_autofireCommand{m_turret},
            m_activateBoosterCommand{m_turret},
            m_chassis{drivers, config::chassis::k_defaultConfig},
            m_fieldMecanumCommand{m_chassis, drivers.inputHandler, config::motion::k_defaultMotionConfig}
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
        m_chassis.setDefaultCommand(&m_fieldMecanumCommand);
        //m_drivers.commandScheduler.addCommand(&m_activateBoosterCommand);
    }
    
    void Pierce::registerIoMappings()
    {
        m_drivers.commandMapper.addMap(&m_activateBoosterCommandMapping);
        m_drivers.commandMapper.addMap(&m_activateAutofireCommandMapping);
    }
}