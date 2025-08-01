#ifndef FANG_ROBOTICS_MCB_TESET_CONTROL_MOCK_RAIL_RAIL_CHASSIS_MOCKS_HPP
#define FANG_ROBOTICS_MCB_TESET_CONTROL_MOCK_RAIL_RAIL_CHASSIS_MOCKS_HPP
#include "rail/mock/chassis/iquad_drive_mock.hpp"
#include "wrap/rail/chassis/quad_data_alias.hpp"
namespace fang::chassis
{
    using IQuadDriveMock = rail::chassis::IQuadDriveMock<QuadRPM>;

}
#endif