#ifndef FANG_ROBOTICS_MCB_CHASSIS_INPUT_HANDLER_HPP
#define FANG_ROBOTICS_MCB_CHASSIS_INPUT_HANDLER_HPP
#include "configuration/unitaliases.hpp"
#include "configuration/mathaliases.hpp"
#include "tap/communication/serial/remote.hpp"

namespace control
{
    namespace chassis
    {
        class ChassisInputHandler
        {
        public:
            using Remote = tap::communication::serial::Remote;

            ChassisInputHandler(Remote& remote);
            /**
             * Returns the desired translation motion
             * Depending on which mode is used, this could be relative to the robot chassis,
             * the field, or the 
             * The barrel facing forward is the positive y direciton.
             * This interpets the dji remote inputs
             */
            logic::chassis::Velocity2D getRemoteTranslation() const;

            /**
             * Returns the amount that the turret should rotate
             */
            Radians getRemoteAngularDisplacement() const;

            /**
             * How fast either the chassis or the turret should
             * be rotated
             */
            RPM getRemoteRotation() const;
        private:
            Remote& m_remote;
        };
    }// namespace chassis
}//namespace control
#endif