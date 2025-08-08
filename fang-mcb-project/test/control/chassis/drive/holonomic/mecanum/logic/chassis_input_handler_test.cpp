#include "driver/drivers.hpp"
#include "control/chassis/chassis_input_handler.hpp"

#include "wrap/units/units_alias.hpp"
#include "tap/mock/remote_mock.hpp"
#include "tap/communication/serial/remote.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tuple>
using namespace fang;
using AbstractVector2D = fang::math::AbstractVector2D;
using ::testing::Return;
using namespace units::literals;

using Remote = tap::communication::serial::Remote;
using Channel = Remote::Channel;
using Key = Remote::Key;

static const fang::chassis::ChassisInputHandler::RemoteConfig k_chassisInputRemoteConfig
{
    Channel::LEFT_HORIZONTAL,   //xTranslation
    Channel::LEFT_VERTICAL,     //yTranslation
    Channel::WHEEL              //rotation
};
static const fang::chassis::ChassisInputHandler::KeyboardConfig k_chassisInputKeyboardConfig
{
    Key::W, //forward
    Key::S, //backward
    Key::A, //left
    Key::D  //right
};
static const fang::chassis::ChassisInputHandler::Config k_chassisInputConfig
{
    k_chassisInputRemoteConfig,
    k_chassisInputKeyboardConfig
};

//TODO: change tuples into structs AHHH
class ChassisInputHandlerTest :  public ::testing::TestWithParam<std::tuple<double, double, double, fang::math::AbstractVector2D, double, double>>
{
protected:
    const double m_leftJoystickHorizontal{std::get<0>(GetParam())};
    const double m_leftJoystickVertical{std::get<1>(GetParam())};
    const double m_rightJoystickHorizontal{std::get<2>(GetParam())};

    const fang::math::AbstractVector2D m_expectedTranslation{std::get<3>(GetParam())};
    const double m_expectedRPM{std::get<4>(GetParam())};
    const double m_expectedDisplacement{std::get<5>(GetParam())};

    Drivers m_drivers{};
    tap::mock::RemoteMock& m_remote{m_drivers.remote};

    fang::chassis::ChassisInputHandler m_chassisInputHandler{m_remote, k_chassisInputConfig};
    
};

TEST_P(ChassisInputHandlerTest, inputHandlingTest)
{
    using Channel = tap::communication::serial::Remote::Channel;
    ON_CALL(m_drivers.remote, getChannel(k_chassisInputConfig.remoteConfig.xTranslationChannel))
        .WillByDefault(Return(m_leftJoystickHorizontal));

    ON_CALL(m_drivers.remote, getChannel(k_chassisInputConfig.remoteConfig.yTranslationChannel))
        .WillByDefault(Return(m_leftJoystickVertical));

    ON_CALL(m_drivers.remote, getChannel(k_chassisInputConfig.remoteConfig.rotationChannel))
        .WillByDefault(Return(m_rightJoystickHorizontal));

    //Check answers
    const fang::math::AbstractVector2D translationOutput{m_chassisInputHandler.getRemoteTranslation()};
    const double rotationOutput{m_chassisInputHandler.getRemoteRotation()};

    EXPECT_DOUBLE_EQ(translationOutput.x, m_expectedTranslation.x);
    EXPECT_DOUBLE_EQ(translationOutput.y, m_expectedTranslation.y);
    EXPECT_DOUBLE_EQ(rotationOutput, m_expectedRPM);
}

INSTANTIATE_TEST_SUITE_P(zeroTest, ChassisInputHandlerTest, testing::Values(std::make_tuple(0.0, 0.0, 0.0, AbstractVector2D{0.0, 0.0}, 0_rpm, 0_rad)));

INSTANTIATE_TEST_SUITE_P(maxTest, ChassisInputHandlerTest,
    testing::Values(std::make_tuple(1.0, 1.0, 1.0, AbstractVector2D{1.0, 1.0}, 1.0, 1.0)));


INSTANTIATE_TEST_SUITE_P(minTest, ChassisInputHandlerTest,
    testing::Values(std::make_tuple(-1.0, -1.0, -1.0, AbstractVector2D{-1.0, -1.0}, -1.0, -1.0)));