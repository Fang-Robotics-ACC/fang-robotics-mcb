#include "mecanumcalculator.hpp"
namespace logic
{
    namespace chassis
    {

        //lx is half of the total horizontal distance between the wheels
        //ly is half of the total vertical distance between the wheels
        MecanumCalculator::MecanumCalculator(const Meters& horizontalWheelDistance,
                                             const Meters& verticalWheelDistance,
                                             const Meters& wheelRadius):
            mk_wheelDistanceConstant{(horizontalWheelDistance / 2.0) + (verticalWheelDistance / 2.0)},
            mk_wheelRadius{wheelRadius}
        {}
        
        Velocity2D MecanumCalculator::getTranslation() const
        {
            MetersPerSecond xVelocity{(mk_wheelRadius / 4.0) 
                                    * (m_quadDriveData.frontLeft - m_quadDriveData.frontRight
                                     - m_quadDriveData.rearLeft  + m_quadDriveData.rearRight)};

            MetersPerSecond yVelocity{(mk_wheelRadius / 4.0) 
                                    * (+ m_quadDriveData.frontLeft + m_quadDriveData.frontRight
                                       + m_quadDriveData.rearLeft  + m_quadDriveData.rearRight)};

            return Velocity2D{xVelocity, yVelocity};
        }

        RPM MecanumCalculator::getRotation() const
        {

        //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
        //Equation 26
        const RPM rotationSum{- m_quadDriveData.frontLeft + m_quadDriveData.frontRight
                              - m_quadDriveData.rearLeft  + m_quadDriveData.rearRight};
        const auto rotationConstant{mk_wheelRadius / (4.0 * mk_wheelDistanceConstant)};

        return rotationConstant * rotationSum; 
        }
    }
}