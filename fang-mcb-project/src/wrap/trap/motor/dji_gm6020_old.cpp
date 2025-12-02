#include "dji_gm6020_old.hpp"
#include "driver/motor/util/gearbox_speed.hpp"

#include <cassert>

namespace trap
{
    namespace motor
    {
        DjiGM6020Old::DjiGM6020Old(Drivers& drivers, const Config& config)
        : DjiGM6020Old{drivers, config.motorId, config.canBus, config.name,
                   config.inverted, config.gearRatio, config.speedPidConfig, config.currentControl}
        {
        }

        DjiGM6020Old::DjiGM6020Old(Drivers& drivers, tap::motor::MotorId motorId, tap::can::CanBus canBus,
                           const char* name, bool inverted, double gearRatio, const DjiSpeedPid::Config& speedPidConfig, bool currentControl)
        : m_djiMotor{&drivers, 
                     static_cast<tap::motor::MotorId>(static_cast<int>(motorId) + mk_GM6020CANAddressOffset),//Hack of hacks
                     canBus, 
                     inverted,
                     name, 
                     currentControl, 
                     1.0}, //Gear ratio is for extern encoder, causes glitches if non-zero with no external encoder
          m_gearRatio{gearRatio},
          m_speedPid{speedPidConfig}
        {
            //assert(static_cast<DjiMotorOutput>(speedPidConfig.maxOutput) <= k_maxOutput && "pid can exceed max output!!!");
        }

        void DjiGM6020Old::update()
        {
            trap::algorithms::WrappedRadians current{getPosition()};
            const Radians error{current.minDifference(m_targetPosition)};
            setDesiredOutput(m_speedPid.runController(error));
        }

        void DjiGM6020Old::setTargetPosition(const Radians& targetPosition)
        {
            m_targetPosition = targetPosition;
        }

        Radians DjiGM6020Old::getPosition() const
        {
            return Radians{m_djiMotor.getEncoder()->getPosition().getWrappedValue()};
        }

        void DjiGM6020Old::initialize()
        {
            m_djiMotor.initialize();
        }

        void DjiGM6020Old::setDesiredOutput(DjiMotorOutput desiredOutput)
        {
            //assert(-k_maxOutput <= desiredOutput && desiredOutput <= k_maxOutput && "Max output exceeded");
            m_djiMotor.setDesiredOutput(desiredOutput);
        }

        bool DjiGM6020Old::isMotorOnline() const
        {
            return m_djiMotor.isMotorOnline();
        }

        Celsius DjiGM6020Old::getTemperature() const
        {
            return Celsius{m_djiMotor.getTemperature()};
        }

        tap::can::CanBus DjiGM6020Old::getCanBus() const
        {
            return m_djiMotor.getCanBus();
        }

        const char* DjiGM6020Old::getName() const
        {
            return m_djiMotor.getName();
        }
    }
}
