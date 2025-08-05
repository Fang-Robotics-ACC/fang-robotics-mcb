#ifndef FANG_ROBOTKICS_MCB_TEST_WRAP_RAIL_CHASSIS_QUAD_DRIVE_MATCH_HPP
#define FANG_ROBOTKICS_MCB_TEST_WRAP_RAIL_CHASSIS_QUAD_DRIVE_MATCH_HPP
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "wrap/rail/chassis/quad_drive_data.hpp"
namespace fang::chassis
{
    MATCHER_P(quadDriveDataEq, quad, ""){return quad == arg;}
}
#endif