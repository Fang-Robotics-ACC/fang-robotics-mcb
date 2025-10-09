#include "dji_m3508.hpp"
#include "driver/motor/util/gearbox_speed.hpp"

#include "tap/errors/create_errors.hpp"
#include <cassert>

namespace trap
{
    namespace motor
    {
        DjiM3508Old::DjiM3508Old(Drivers& drivers, const Config& config)
        : DjiM3508Old{drivers, config.motorId, config.canBus, config.name,
                   config.inverted, config.gearRatio, config.speedPidConfig}
        {
        }

        DjiM3508Old::DjiM3508Old(Drivers& drivers, tap::motor::MotorId motorId, tap::can::CanBus canBus,
                           const char* name, bool inverted, double gearRatio, const DjiSpeedPid::Config& speedPidConfig)
        : m_drivers{drivers},
          m_djiMotor{&drivers, motorId, canBus, inverted, name, mk_requiredCurrentMode, gearRatio},//Gear ratio is for extern encoder, causes glitches if non-zero with no external encoder
          m_gearRatio{gearRatio},
          m_speedPid{speedPidConfig}
        {
            //assert(static_cast<DjiMotorOutput>(speedPidConfig.maxOutput) <= k_maxOutput && "pid can exceed max output!!!");
        }

        void DjiM3508Old::update()
        {
            const RPM error{m_targetSpeed - getSpeed()};
            setDesiredOutput(m_speedPid.runController(error));
        }

        void DjiM3508Old::setTargetSpeed(const RPM& targetSpeed)
        {
            m_targetSpeed = fang::motor::shaftToMotorSpeed(targetSpeed, m_gearRatio);
        }

        RPM DjiM3508Old::getSpeed() const
        {
            return fang::motor::motorToShaftSpeed(RPM{m_djiMotor.getShaftRPM()}, m_gearRatio);
        }

        void DjiM3508Old::initialize()
        {
            m_djiMotor.initialize();
        }

        void DjiM3508Old::setDesiredOutput(DjiMotorOutput desiredOutput)
        {

            //if (!(-k_maxOutput <= desiredOutput && desiredOutput <= k_maxOutput))
            //{
            //    RAISE_ERROR((&m_drivers), "Max output exceeded");
            //}
            
            m_djiMotor.setDesiredOutput(desiredOutput);
        }

        bool DjiM3508Old::isMotorOnline() const
        {
            return m_djiMotor.isMotorOnline();
        }

        Celsius DjiM3508Old::getTemperature() const
        {
            return Celsius{m_djiMotor.getTemperature()};
        }

        tap::can::CanBus DjiM3508Old::getCanBus() const
        {
            return m_djiMotor.getCanBus();
        }

        const char* DjiM3508Old::getName() const
        {
            return m_djiMotor.getName();
        }
    }
}