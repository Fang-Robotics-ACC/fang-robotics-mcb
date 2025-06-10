#include "dji_m3508.hpp"
#include "gearbox_speed.hpp"

#include "tap/errors/create_errors.hpp"
#include <cassert>

namespace trap
{
    namespace motor
    {
        DjiM3508::DjiM3508(Drivers& drivers, const Config& config)
        : DjiM3508{drivers, config.motorId, config.canBus, config.name,
                   config.inverted, config.gearRatio, config.speedPidConfig}
        {
        }

        DjiM3508::DjiM3508(Drivers& drivers, tap::motor::MotorId motorId, tap::can::CanBus canBus,
                           const char* name, bool inverted, double gearRatio, const DjiSpeedPid::Config& speedPidConfig)
        : m_drivers{drivers},
          m_djiMotor{&drivers, motorId, canBus, inverted, name, mk_requiredCurrentMode, gearRatio},
          m_gearRatio{gearRatio},
          m_speedPid{speedPidConfig}
        {
            //assert(static_cast<DjiMotorOutput>(speedPidConfig.maxOutput) <= k_maxOutput && "pid can exceed max output!!!");
        }

        void DjiM3508::update()
        {
            const RPM error{m_targetSpeed - getSpeed()};
            setDesiredOutput(m_speedPid.runController(error));
        }

        void DjiM3508::setTargetSpeed(const RPM& targetSpeed)
        {
            m_targetSpeed = motors::shaftToMotorSpeed(targetSpeed, m_gearRatio);
        }

        RPM DjiM3508::getSpeed() const
        {
            return motors::motorToShaftSpeed(RPM{m_djiMotor.getShaftRPM()}, m_gearRatio);
        }

        void DjiM3508::initialize()
        {
            m_djiMotor.initialize();
        }

        void DjiM3508::setDesiredOutput(DjiMotorOutput desiredOutput)
        {

            //if (!(-k_maxOutput <= desiredOutput && desiredOutput <= k_maxOutput))
            //{
            //    RAISE_ERROR((&m_drivers), "Max output exceeded");
            //}
            
            m_djiMotor.setDesiredOutput(desiredOutput);
        }

        bool DjiM3508::isMotorOnline() const
        {
            return m_djiMotor.isMotorOnline();
        }

        Celsius DjiM3508::getTemperature() const
        {
            return Celsius{m_djiMotor.getTemperature()};
        }

        tap::can::CanBus DjiM3508::getCanBus() const
        {
            return m_djiMotor.getCanBus();
        }

        const char* DjiM3508::getName() const
        {
            return m_djiMotor.getName();
        }
    }
}