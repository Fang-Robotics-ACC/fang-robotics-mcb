#include "basemecanummotioncalculator.h"
#include "chassislogicaliases.h"


namespace logic
{
    namespace chassis
    {

        void BaseMecanumMotionCalculator::setQuadDriveData(const QuadDriveData& quadDriveData)
        {
            m_quadDriveData = quadDriveData;
        }

        Translation2D BaseMecanumMotionCalculator::getTranslation() const
        {
            //Refer to equation 22 in https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
            const double ySpeedSum{m_quadDriveData.frontLeft + m_quadDriveData.frontRight
                            + m_quadDriveData.rearLeft  + m_quadDriveData.rearRight};
            const double y{ySpeedSum*(0.25)}; //The formula multiplies the sum by 1/4 of the radius

            //Refer to equation 23 in https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
            const double xSpeedSum{-m_quadDriveData.frontLeft + m_quadDriveData.frontRight
                            + m_quadDriveData.rearLeft  - m_quadDriveData.rearRight};
            const double x{ySpeedSum*(0.25)}; //The formula multiplies the sum by 1/4 of the radius

            return Translation2D{x, y};
        }
    }
}