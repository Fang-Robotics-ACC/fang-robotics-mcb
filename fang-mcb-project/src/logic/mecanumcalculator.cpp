#include "mecanumcalculator.hpp"
#include "unitaliases.hpp"
#include <iostream>
namespace logic
{
    namespace chassis
    {

        void MecanumCalculator::setWheelSpeeds(const QuadDriveData& quadDriveData)
        {
            //The input is in RPM; however, the implementation needs the angular velocity in radians
            //This is a quick fix. A more proper way to do this is to add operator overloads for the templates
            m_quadDriveData.frontLeft = quadDriveData.frontLeft;
            m_quadDriveData.frontRight = quadDriveData.frontRight;
            m_quadDriveData.rearLeft = quadDriveData.rearLeft;
            m_quadDriveData.rearRight = quadDriveData.rearRight;
        }

        //lx is half of the total horizontal distance between the wheels
        //ly is half of the total vertical distance between the wheels
        MecanumCalculator::MecanumCalculator(const Meters& horizontalWheelDistance,
                                             const Meters& verticalWheelDistance,
                                             const Meters& wheelRadius):
            mk_wheelDistanceConstant{(horizontalWheelDistance)},
            mk_wheelRadius{wheelRadius}
        {}
        
        Velocity2D MecanumCalculator::getTranslation() const
        {
            MetersPerSecond xVelocity{((mk_wheelRadius / 4.0) 
                                    * (m_quadDriveData.frontLeft - m_quadDriveData.frontRight
                                     - m_quadDriveData.rearLeft  + m_quadDriveData.rearRight)).to<double>()};

            MetersPerSecond yVelocity{((mk_wheelRadius / 4.0) 
                                    * (  m_quadDriveData.frontLeft + m_quadDriveData.frontRight
                                       + m_quadDriveData.rearLeft  + m_quadDriveData.rearRight)).to<double>()};

            return Velocity2D{xVelocity, yVelocity};
        }

        RPM MecanumCalculator::getRotation() const
        {

        //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
        //Equation 26
        const RadiansPerSecond rotationSum{- m_quadDriveData.frontLeft + m_quadDriveData.frontRight
                              - m_quadDriveData.rearLeft  + m_quadDriveData.rearRight};
        const auto rotationConstant{mk_wheelRadius / (4.0 * mk_wheelDistanceConstant)};

        return rotationConstant * rotationSum; 
        }
        
    }
}