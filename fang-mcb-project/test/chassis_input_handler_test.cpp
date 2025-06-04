#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "control/chassis/chassis_input_handler.hpp"
#include "configuration/chassislogicaliases.hpp"
#include "configuration/motion_control_config.hpp"
#include "unitaliases.hpp"
#include "drivers.hpp"
#include "tap/mock/remote_mock.hpp"
#include "tap/communication/serial/remote.hpp"

#include <tuple>

using AbstractVector2D = math::AbstractVector2D;
using ::testing::Return;
using namespace units::literals;

class ChassisInputHandlerTest :  public ::testing::TestWithParam<std::tuple<double, double, double, math::AbstractVector2D, double, double>>
{
protected:
    const double m_leftJoystickHorizontal{std::get<0>(GetParam())};
    const double m_leftJoystickVertical{std::get<1>(GetParam())};
    const double m_rightJoystickHorizontal{std::get<2>(GetParam())};

    const math::AbstractVector2D m_expectedTranslation{std::get<3>(GetParam())};
    const double m_expectedRPM{std::get<4>(GetParam())};
    const double m_expectedDisplacement{std::get<5>(GetParam())};

    Drivers m_drivers{};
    tap::mock::RemoteMock& m_remote{m_drivers.remote};

    control::chassis::ChassisInputHandler& m_chassisInputHandler{m_drivers.inputHandler.getChassisInputs()};
    
};

TEST_P(ChassisInputHandlerTest, inputHandlingTest)
{
    using Channel = tap::communication::serial::Remote::Channel;
    ON_CALL(m_drivers.remote, getChannel(Channel::LEFT_HORIZONTAL))
        .WillByDefault(Return(m_leftJoystickHorizontal));

    ON_CALL(m_drivers.remote, getChannel(Channel::LEFT_VERTICAL))
        .WillByDefault(Return(m_leftJoystickVertical));

    ON_CALL(m_drivers.remote, getChannel(Channel::RIGHT_HORIZONTAL))
        .WillByDefault(Return(m_rightJoystickHorizontal));

    //Check answers
    const math::AbstractVector2D translationOutput{m_chassisInputHandler.getRemoteTranslation()};
    const double rotationOutput{m_chassisInputHandler.getRemoteRotation()};
    const double angularDisplacementOutput{m_chassisInputHandler.getRemoteAngularDisplacement()};

    EXPECT_DOUBLE_EQ(translationOutput.x, m_expectedTranslation.x);
    EXPECT_DOUBLE_EQ(translationOutput.y, m_expectedTranslation.y);
    EXPECT_DOUBLE_EQ(rotationOutput, m_expectedRPM);
    EXPECT_DOUBLE_EQ(angularDisplacementOutput, m_expectedDisplacement);
}

INSTANTIATE_TEST_SUITE_P(zeroTest, ChassisInputHandlerTest, testing::Values(std::make_tuple(0.0, 0.0, 0.0, AbstractVector2D{0.0, 0.0}, 0_rpm, 0_rad)));

INSTANTIATE_TEST_SUITE_P(maxTest, ChassisInputHandlerTest,
    testing::Values(std::make_tuple(1.0, 1.0, 1.0, AbstractVector2D{1.0, 1.0}, 1.0, 1.0)));


INSTANTIATE_TEST_SUITE_P(minTest, ChassisInputHandlerTest,
    testing::Values(std::make_tuple(-1.0, -1.0, -1.0, AbstractVector2D{-1.0, -1.0}, -1.0, -1.0)));