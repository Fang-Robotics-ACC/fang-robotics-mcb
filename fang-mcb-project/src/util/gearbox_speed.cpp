#include "configuration/unitaliases.hpp"

namespace motors
{
    RPM motorToShaftSpeed(const RPM& motorSpeed, double gearRatio)
    {
        //The gear ratio is how many times the motor rotates per gear rotation
        //Therefore the motor speed must be divide by the gear ratio
        return motorSpeed / gearRatio;
    }

    RPM shaftToMotorSpeed(const RPM& shaftSpeed, double gearRatio)
    {

        //The gear ratio is how many times the motor rotates per gear rotation
        //Therefore the shaft speed must be multiplied by the gear ratio
        //To figure out how many times to motor rotates
        return shaftSpeed * gearRatio;
    }
}