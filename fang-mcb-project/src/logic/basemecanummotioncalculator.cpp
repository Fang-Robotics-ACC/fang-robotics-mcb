#include "basemecanummotioncalculator.h"


namespace logic
{
    namespace chassis
    {

        void BaseMecanumMotionCalculator::setQuadDriveData(const QuadDriveData& quadDriveData)
        {
            m_quadDriveData = quadDriveData;
        }
    }
}