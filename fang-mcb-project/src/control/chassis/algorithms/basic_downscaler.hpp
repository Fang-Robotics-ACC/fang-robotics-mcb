#ifndef FANG_ROBOTICS_MCB_CHASSIS_ALGORITHMS_BASIC_DOWNSCALERS_HPP
#define FANG_ROBOTICS_MCB_CHASSIS_ALGORITHMS_BASIC_DOWNSCALERS_HPP
#include "wrap/units/units_alias.hpp"

namespace fang::chassis
{
    /**
     * Small downscaler for finding an amount to downscale for the shuriken
     * mode in order to conserve power
     */
    class BasicDownscaler
    {
    public:
        /** The higher the downscale coefficient, the less downscaling it will do
         * with respect to speed
         * https://www.desmos.com/calculator/5xqaxqilmnj
         */
        static double basicDownscale(double speed, double coefficient);

        /**
         * The high the downscale coefficient, the less downscaling it will do
         * with respect to speed
         * https://www.desmos.com/calculator/5xqaxqilmnj
         */
        BasicDownscaler(double downscaleCoefficient);
        double getDownscale (const MetersPerSecond& speed) const;

    private:
        const double m_downscaleCoefficient;
    };
}
#endif