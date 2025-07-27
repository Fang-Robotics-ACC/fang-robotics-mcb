#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSIS_FORMULAE_AZRIEL_SHREDDER_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSIS_FORMULAE_AZRIEL_SHREDDER_HPP
namespace fang::chassis
{
    /**
     * Raven Asher Raziel's anti CV algorithm!
     * Hopefully this is not relevant to military applications :D
     * 
     * This returns a scaling coefficient to be used in relation to rotation or even translation
     * 
     * https://www.desmos.com/calculator/f3662079d3
     * input - the control value, could be time phase, or anything, really 
     * biteDepth - how much the shredder decreases the speed in a "bite" it should be within [0,1]
     * biteForce - how steep the "bite" is, it must be a posiive integer
     * period - how often a bite happens, it should be a positive real number
     * phase, the underlying function involves sine in radians
     */
    class AzrielShredder
    {
    public:
        struct Config
        {
            double biteDepth;
            int biteForce;
            double period;
            double phase = 0;
        };

        static double razielKalmanShredder(double input, double biteDepth, int biteForce,  double period, double phase);

        AzrielShredder(const Config& config);

        void setBiteDepth(double biteDepth);
        void setBiteForce(int biteForce);
        void setPeriod(double period);
        void setPhase(double phase);
        double getScalingFactor(double input) const;
    private:
        //non-const so that we can add setters for the future
        double m_biteDepth;
        int m_biteForce;
        double m_period;
        double m_phase;
    };
}
#endif