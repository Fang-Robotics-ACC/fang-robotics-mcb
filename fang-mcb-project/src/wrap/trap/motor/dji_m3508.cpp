#include "dji_m3508.hpp"
namespace trap
{
    namespace motor
    {
        DjiM3508::DjiM3508(Drivers& drivers, const Config& config)
        : DjiM3508{drivers, config.motorId, config.canBus, config.name,
                   config.inverted, config.currentControl, config.gearRatio}
        {}

        DjiM3508::DjiM3508(Drivers& drivers, tap::motor::MotorId motorId, tap::can::CanBus canBus,
                           const char* name, bool inverted, bool currentControl, double gearRatio)
        : m_djiMotor{&drivers, motorId, canBus, inverted, name, currentControl, gearRatio}
        {}

        void DjiM3508::initialize()
        {
            m_djiMotor.initialize();
        }

        void DjiM3508::setDesiredOutput(int16_t desiredOutput)
        {
            m_djiMotor.setDesiredOutput(desiredOutput);
        }
    }
}