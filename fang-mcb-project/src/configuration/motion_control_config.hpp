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
         * They should be positive.
         */
        struct MotionConfig
        {
            MetersPerSecond xTranslationMax;
            MetersPerSecond yTranslationMax;
            RPM rotationMax;
        };

        static const MotionConfig k_defaultMotionConfig
        {
            xTranslationMax = 5_mph,
            yTranslationMax = 10_mph,
            rotationMax = 60_rpm
        };
    }
}
#endif
