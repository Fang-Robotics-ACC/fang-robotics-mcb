#ifndef FANG_ROBOTICS_MCB_TURRET_INPUT_HANDLER_HPP
#define FANG_ROBOTICS_MCB_TURRET_INPUT_HANDLER_HPP
namespace control
{
    namespace turret
    {
        class TurretInputHandler
        {
        public:
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
        }
    }
}
#endif