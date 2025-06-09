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
            /**
             * Positive is upwards
             */
            double getPitch() const;
            /**
             * Positive is counterclockwise
             * 
             */
            double getYaw() const;
        private:
            double getRemotePitch() const;
            double getRemoteYaw() const; 

            Remote& m_remote;
        };
    }
}
#endif