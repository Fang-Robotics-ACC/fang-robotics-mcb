#include "raziel_kalman_shredder.hpp"

#include <numbers>
#include <math.h>
namespace control::chassis
{
    double RazielKalmanShredder::razielKalmanShredder(double input, int biteDepth, double biteForce,  double period, double phase)
    {
        //https://www.desmos.com/calculator/e19d96ky1e

        //We need to convert the period into the coefficient form
        //Refer to high school pre-cal for more inormation
        const double innerSineCoefficient{2 * std::numbers::pi / period};
        const double phasedInput{input - phase};
        const double sinedValue{std::sin(innerSineCoefficient* phasedInput)};
        const double evenPower(2 * biteForce);

        //The power must be even to prevent it from going out of bounds
        //The purpose for this part is to add the ability to make the dips "sharper"
        const double sharpened{std::pow(sinedValue, evenPower)};

        //Subtract from one so that the bite depth deals to decreasing the scaling
        const double scalingShredFactor{1 - biteDepth * sharpened};
        return scalingShredFactor;
    }

    RazielKalmanShredder::RazielKalmanShredder(const Config& config)
    :   m_biteDepth{config.biteDepth},
        m_biteForce{config.biteForce},
        m_period{config.period},
        m_phase{config.phase}
    {
    }
};
