#include "turret_subsystem.hpp"

namespace control
{
    namespace turret
    {
        TurretSubsystem::TurretSubsystem(Drivers& drivers, const Config& config)
        :   Subsystem{&drivers},
            m_gimbal{drivers, config.gimbalConfig}
        {
        }

        void TurretSubsystem::initialize()
        {
            m_gimbal.initialize();
        }

        void TurretSubsystem::refresh()
        {
            m_gimbal.update();
        }

        void TurretSubsystem::setFieldYaw(const Radians& yaw)
        {
            m_gimbal.setYaw(yaw);
        }

        void TurretSubsystem::setPitch(const Radians& pitch)
        {
            m_gimbal.setPitch(pitch);
        }


    }
}