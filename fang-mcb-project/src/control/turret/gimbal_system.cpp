#include "control/turret/gimbal_system.hpp"
namespace control
{
    namespace turret
    {
        GimbalSystem::GimbalSystem(Drivers& drivers, const Config& config)
        :   m_minPitch{config.minPitch}, m_maxPitch{config.maxPitch},
            m_pitchMotor{drivers, config.pitchMotorConfig},
            m_yawMotor{drivers, config.yawMotorConfig}
        {
        }
    }
}