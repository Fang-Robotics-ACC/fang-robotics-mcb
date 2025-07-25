#ifndef FANG_ROBOTICS_MCB_TEST_MOCK_MOTOR_RAIL_RAIL_MOTOR_MOCKS_HPP
#define FANG_ROBOTICS_MCB_TEST_MOCK_MOTOR_RAIL_RAIL_MOTOR_MOCKS_HPP
#include "wrap/units/units_alias.hpp"

#include <rail/mock/motor/ispeed_motor_mock.hpp>
namespace fang::motor
{
    using ISpeedMotorMock = rail::motor::ISpeedMotorMock<RPM>;
}
#endif