#include "imu.hpp"
namespace trap::communication::sensors
{
    Imu::Imu(ImuInterface& imu)
    :   m_imu{imu}
    {
    }

    Radians Imu::getPitch() const
    {
        return Radians{m_imu.getPitch()};
    }

    Radians Imu::getYaw() const
    {
        return Radians{m_imu.getYaw()};
    }
    Radians Imu::getRoll() const
    {
        return Radians{m_imu.getRoll()};
    }


}
