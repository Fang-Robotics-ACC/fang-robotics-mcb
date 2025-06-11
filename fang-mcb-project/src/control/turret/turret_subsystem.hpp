#ifndef FANG_ROBOTICS_MCB_TURRET_SUBSYSTEM_HPP
#define FANG_ROBOTICS_MCB_TURRET_SUBSYSTEM_HPP
#include "control/turret/gimbal_system.hpp"

#include "drivers.hpp"
#include "unitaliases.hpp"

#include "tap/control/subsystem.hpp"
namespace control
{
    namespace turret
    {
        class TurretSubsystem : public virtual tap::control::Subsystem
        {
        public:
            struct Config
            {
                GimbalSystem::Config gimbalConfig;
            };

            virtual void refresh() override;
            TurretSubsystem(Drivers& drivers, const Config& config);
            void setFieldYaw(const Radians& yaw);


        private:
            GimbalSystem m_gimbal;
        };
    }
}
#endif