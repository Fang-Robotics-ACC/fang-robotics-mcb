#ifndef FANG_ROBOTICS_MCB_TURRET_INPUT_HANDLER_HPP
#define FANG_ROBOTICS_MCB_TURRET_INPUT_HANDLER_HPP
#include "tap/communication/serial/remote.hpp"
namespace control
{
    namespace turret
    {
        class TurretInputHandler
        {
        public:
            using Remote = tap::communication::serial::Remote;

            TurretInputHandler(Remote& remote);

            double getPitch() const;
            double getYaw() const;
        private:
            Remote& m_remote;
        };
    }
}
#endif