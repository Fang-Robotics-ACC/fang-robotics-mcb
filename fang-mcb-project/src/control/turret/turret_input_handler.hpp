#ifndef FANG_ROBOTICS_MCB_TURRET_INPUT_HANDLER_HPP
#define FANG_ROBOTICS_MCB_TURRET_INPUT_HANDLER_HPP
#include "control/input_type.hpp"

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
            void setInputType(InputType inputType);
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
            InputType m_inputType{InputType::REMOTE};
        };
    }
}
#endif