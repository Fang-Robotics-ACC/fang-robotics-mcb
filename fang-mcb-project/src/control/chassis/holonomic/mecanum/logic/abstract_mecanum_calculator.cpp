#include "abstract_mecanum_calculator.hpp"

namespace fang::chassis
{
    void AbstractMecanumCalculator::setWheelSpeeds(const AbstractWheelSpeeds& quadDriveData)
    {
        quadDriveData_ = quadDriveData;
    }

    AbstractVelocity2D AbstractMecanumCalculator::getTranslation() const
    {
        //Refer to equation 22 in https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
        const double ySpeedSum{quadDriveData_.frontLeft + quadDriveData_.frontRight
                        + quadDriveData_.rearLeft  + quadDriveData_.rearRight};
        const double y{ySpeedSum * 0.25}; //The formula multiplies the sum by 1/4 of the radius
        //Refer to equation 23 in https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
        //Adapted so right direction is positive
        const double xSpeedSum{quadDriveData_.frontLeft - quadDriveData_.frontRight
                        - quadDriveData_.rearLeft  + quadDriveData_.rearRight};
        const double x{xSpeedSum * 0.25}; //The formula multiplies the sum by 1/4 of the radius
        return AbstractVelocity2D{x, y};
    }
    //Refer to equation 24
    //Positive offset values are counterclockwise
    double AbstractMecanumCalculator::getRotationOffset() const
    {
        const double offsetSum{-quadDriveData_.frontLeft + quadDriveData_.frontRight
                        - quadDriveData_.rearLeft  + quadDriveData_.rearRight};
        //Refer to the formula. Essentially, if you don't divide by 4, everything is 4 times as larger
        //Than expected.
        return offsetSum * 0.25;
    }
}
