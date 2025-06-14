#include "dji_m2006.hpp"
#include "gearbox_speed.hpp"

#include <cassert>

namespace trap
{
    namespace motor
    {
        DjiM2006::DjiM2006(Drivers& drivers, const Config& config)
        : DjiM2006{drivers, config.motorId, config.canBus, config.name,
                   config.inverted, config.gearRatio, config.speedPidConfig}
        {
        }

        DjiM2006::DjiM2006(Drivers& drivers, tap::motor::MotorId motorId, tap::can::CanBus canBus,
                           const char* name, bool inverted, double gearRatio, const DjiSpeedPid::Config& speedPidConfig)
        : m_djiMotor{&drivers, motorId, canBus, inverted, name, mk_requiredCurrentMode, gearRatio},
          m_gearRatio{gearRatio},
          m_speedPid{speedPidConfig}
        {
            //assert(static_cast<DjiMotorOutput>(speedPidConfig.maxOutput) <= k_maxOutput && "pid can exceed max output!!!");
        }

        void DjiM2006::update()
        {
            const RPM error{m_targetSpeed - getSpeed()};
            setDesiredOutput(m_speedPid.runController(error));
        }

        void DjiM2006::setTargetSpeed(const RPM& targetSpeed)
        {
            m_targetSpeed = motors::shaftToMotorSpeed(targetSpeed, m_gearRatio);
        }

        RPM DjiM2006::getSpeed() const
        {
            return motors::motorToShaftSpeed(RPM{m_djiMotor.getShaftRPM()}, m_gearRatio);
        }

        void DjiM2006::initialize()
        {
            m_djiMotor.initialize();
        }

        void DjiM2006::setDesiredOutput(DjiMotorOutput desiredOutput)
        {
            //assert(-k_maxOutput <= desiredOutput && desiredOutput <= k_maxOutput && "Max output exceeded");
            m_djiMotor.setDesiredOutput(desiredOutput);
        }

        bool DjiM2006::isMotorOnline() const
        {
            return m_djiMotor.isMotorOnline();
        }

        Celsius DjiM2006::getTemperature() const
        {
            return Celsius{m_djiMotor.getTemperature()};
        }

        tap::can::CanBus DjiM2006::getCanBus() const
        {
            return m_djiMotor.getCanBus();
        }

        const char* DjiM2006::getName() const
        {
            return m_djiMotor.getName();
        }
    }
}