#ifndef FANG_ROBOTICS_MCB_TEST_WRAP_RAIL_CHASSIS_EXPECT_QUAD_DRIVE_DATA_EQ_HPP
#define FANG_ROBOTICS_MCB_TEST_WRAP_RAIL_CHASSIS_EXPECT_QUAD_DRIVE_DATA_EQ_HPP

#include "wrap/rail/chassis/quad_drive_data.hpp"
#include <gtest/gtest.h>

namespace fang::chassis
{
    template<typename Data>
    void expectQuadDriveDataEq(const QuadDriveData<Data>& quad1, const QuadDriveData<Data>& quad2)
    {
        EXPECT_DOUBLE_EQ(quad1.frontLeft, quad2.frontLeft);
        EXPECT_DOUBLE_EQ(quad1.frontRight, quad2.frontRight);
        EXPECT_DOUBLE_EQ(quad1.rearLeft, quad2.rearLeft);
        EXPECT_DOUBLE_EQ(quad1.rearRight, quad2.rearRight);
    }
}
#endif

