#include "dji_gm6020.hpp"
#include "gearbox_speed.hpp"

#include <cassert>

namespace trap
{
    namespace motor
    {
        DjiGM6020::DjiGM6020(Drivers& drivers, const Config& config)
        : DjiGM6020{drivers, config.motorId, config.canBus, config.name,
                   config.inverted, config.gearRatio, config.speedPidConfig, config.currentControl}
        {
        }

        DjiGM6020::DjiGM6020(Drivers& drivers, tap::motor::MotorId motorId, tap::can::CanBus canBus,
                           const char* name, bool inverted, double gearRatio, const DjiSpeedPid::Config& speedPidConfig, bool currentControl)
        : m_djiMotor{&drivers, 
                     static_cast<tap::motor::MotorId>(static_cast<int>(motorId) + mk_GM6020CANAddressOffset),//Hack of hacks
                     canBus, 
                     inverted,
                     name, 
                     currentControl, 
                     gearRatio},
          m_speedPid{speedPidConfig}
        {
            assert(static_cast<DjiMotorOutput>(speedPidConfig.maxOutput) <= k_maxOutput && "pid can exceed max output!!!");
        }

        void DjiGM6020::update()
        {
            const RPM error{m_targetSpeed - getSpeed()};
            setDesiredOutput(m_speedPid.runController(error));
        }

        void DjiGM6020::setTargetSpeed(const RPM& targetSpeed)
        {
            m_targetSpeed = motors::shaftToMotorSpeed(targetSpeed, m_gearRatio);
        }

        RPM DjiGM6020::getSpeed() const
        {
            return motors::motorToShaftSpeed(RPM{m_djiMotor.getShaftRPM()}, m_gearRatio);
        }

        void DjiGM6020::initialize()
        {
            m_djiMotor.initialize();
        }

        void DjiGM6020::setDesiredOutput(DjiMotorOutput desiredOutput)
        {
            assert(-k_maxOutput <= desiredOutput && desiredOutput <= k_maxOutput && "Max output exceeded");
            m_djiMotor.setDesiredOutput(desiredOutput);
        }

        bool DjiGM6020::isMotorOnline() const
        {
            return m_djiMotor.isMotorOnline();
        }

        Celsius DjiGM6020::getTemperature() const
        {
            return Celsius{m_djiMotor.getTemperature()};
        }

        tap::can::CanBus DjiGM6020::getCanBus() const
        {
            return m_djiMotor.getCanBus();
        }

        const char* DjiGM6020::getName() const
        {
            return m_djiMotor.getName();
        }
    }
}