#ifndef FANG_ROBOTICS_MCB_CHASSIS_FORMULAE_RAZIEL_KALMAN_SHREDDER_HPP
#define FANG_ROBOTICS_MCB_CHASSIS_FORMULAE_RAZIEL_KALMAN_SHREDDER_HPP
namespace control::chassis
{
    /**
     * Raven Asher Raziel's self-named anti CV algorithm!
     * Hopefully this is not relevant to military applications :D
     * 
     * This returns a scaling coefficient to be used in relation to rotation or even translation
     * 
     * https://www.desmos.com/calculator/e19d96ky1e 
     * input - the control value, could be time phase, or anything, really 
     * biteDepth - how much the shredder decreases the speed in a "bite" it should be within [0,1]
     * biteForce - how steep the "bite" is, it must be a posiive integer
     * period - how often a bite happens, it should be a positive real number
     * phase, the underlying function involves sine in radians
     */
    class RazielKalmanShredder
    {
        struct Config
        {
            int biteDepth;
            double biteForce;
            double period;
            double phase = 0;
        };

        static double razielKalmanShredder(double input, int biteDepth, double biteForce,  double period, double phase);

        RazielKalmanShredder(const Config& config);
        void getScalingFactor(double input) const;
    };
}
#endif