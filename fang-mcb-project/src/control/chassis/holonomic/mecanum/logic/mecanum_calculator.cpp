#include "mecanum_calculator.hpp"
#include "unitaliases.hpp"
#include <iostream>
namespace chassis
{
    void MecanumCalculator::setWheelSpeeds(const WheelSpeeds& quadDriveData)
    {
        //The input is in RPM; however, the implementation needs the angular velocity in radians
        //This is a quick fix. A more proper way to do this is to add operator overloads for the templates
        quadDriveData_.frontLeft = quadDriveData.frontLeft;
        quadDriveData_.frontRight = quadDriveData.frontRight;
        quadDriveData_.rearLeft = quadDriveData.rearLeft;
        quadDriveData_.rearRight = quadDriveData.rearRight;

    }
    //lx is half of the total horizontal distance between the wheels
    //ly is half of the total vertical distance between the wheels
    MecanumCalculator::MecanumCalculator(const Meters& horizontalWheelDistance,
                                         const Meters& verticalWheelDistance,
                                         const Meters& wheelRadius):
        kwheelDistanceConstant_{(horizontalWheelDistance + verticalWheelDistance) / 2.0},
        kWheelRadius_{wheelRadius}
    {
    }

    Velocity2D MecanumCalculator::getTranslation() const
    {
        MetersPerSecond xVelocity{((kWheelRadius_ / 4.0)
                                * (quadDriveData_.frontLeft - quadDriveData_.frontRight
                                 - quadDriveData_.rearLeft  + quadDriveData_.rearRight)).to<double>()};
        MetersPerSecond yVelocity{((kWheelRadius_ / 4.0)
                                * (  quadDriveData_.frontLeft + quadDriveData_.frontRight
                                   + quadDriveData_.rearLeft  + quadDriveData_.rearRight)).to<double>()};
        return Velocity2D{xVelocity, yVelocity};
    }

    RPM MecanumCalculator::getRotation() const
    {
        //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
        //Equation 26
        const RadiansPerSecond rotationSum{- quadDriveData_.frontLeft + quadDriveData_.frontRight
                              - quadDriveData_.rearLeft  + quadDriveData_.rearRight};
        const auto rotationConstant{kWheelRadius_ / (4.0 * kwheelDistanceConstant_)};
        return rotationConstant * rotationSum;
    }
}