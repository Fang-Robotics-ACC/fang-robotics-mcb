#ifndef FANG_ROBOTICS_MCB_MOTION_CONTROL_CONFIG_HPP
#define FANG_ROBOTICS_MCB_MOTION_CONTROL_CONFIG_HPP
#include "unitaliases.hpp"
namespace config
{
    namespace motion 
    {
        using namespace units::literals;
        /**
         * These are the values that are scaled
         * 
         * They should be positive
         * 
         * Translation is relative to either the chassis, the field, or the turret
         * Rotation is either for the chassis or the turret
         * angularDisplacementMax is how much the turret is told to turn
         */
        struct MotionConfig
        {
            MetersPerSecond maxTranslation;
            MetersPerSecond maxXTranslation;
            MetersPerSecond maxYTranslation;
            RPM maxRotation;
            Degrees maxAngularDisplacement;
        };

        static const MotionConfig k_defaultMotionConfig
        {
            10_mph, //max translation - for turret based strafe
            10_mph, //maxXtranslation
            10_mph, //maxYTranslatioon
            100_rpm, //maxRotation
            0.5_deg //maxAngularDisplacement
        };
    }
}
#endif
