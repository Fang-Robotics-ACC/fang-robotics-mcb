#include "dji_m2006_old.hpp"
#include "driver/motor/util/gearbox_speed.hpp"

#include <cassert>

namespace trap
{
    namespace motor
    {
        DjiM2006Old::DjiM2006Old(Drivers& drivers, const Config& config)
        : DjiM2006Old{drivers, config.motorId, config.canBus, config.name,
                   config.inverted, config.gearRatio, config.speedPidConfig}
        {
        }

        DjiM2006Old::DjiM2006Old(Drivers& drivers, tap::motor::MotorId motorId, tap::can::CanBus canBus,
                           const char* name, bool inverted, double gearRatio, const DjiSpeedPid::Config& speedPidConfig)
        : m_djiMotor{&drivers, motorId, canBus, inverted, name, mk_requiredCurrentMode, 1.0},//Gear ratio is for external encoder
          m_gearRatio{gearRatio},
          m_speedPid{speedPidConfig}
        {
            //assert(static_cast<DjiMotorOutput>(speedPidConfig.maxOutput) <= k_maxOutput && "pid can exceed max output!!!");
        }

        void DjiM2006Old::update()
        {
            const RPM error{m_targetSpeed - getSpeed()};
            setDesiredOutput(m_speedPid.runController(error));
        }

        void DjiM2006Old::setTargetSpeed(const RPM& targetSpeed)
        {
            m_targetSpeed = fang::motor::shaftToMotorSpeed(targetSpeed, m_gearRatio);
        }

        RPM DjiM2006Old::getSpeed() const
        {
            return fang::motor::motorToShaftSpeed(RPM{m_djiMotor.getShaftRPM()}, m_gearRatio);
        }

        void DjiM2006Old::initialize()
        {
            m_djiMotor.initialize();
        }

        void DjiM2006Old::setDesiredOutput(DjiMotorOutput desiredOutput)
        {
            //assert(-k_maxOutput <= desiredOutput && desiredOutput <= k_maxOutput && "Max output exceeded");
            m_djiMotor.setDesiredOutput(desiredOutput);
        }

        bool DjiM2006Old::isMotorOnline() const
        {
            return m_djiMotor.isMotorOnline();
        }

        Celsius DjiM2006Old::getTemperature() const
        {
            return Celsius{m_djiMotor.getTemperature()};
        }

        tap::can::CanBus DjiM2006Old::getCanBus() const
        {
            return m_djiMotor.getCanBus();
        }

        const char* DjiM2006Old::getName() const
        {
            return m_djiMotor.getName();
        }
    }
}