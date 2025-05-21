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

using Velocity2D = logic::chassis::Velocity2D;
using ::testing::Return;
using namespace units::literals;

const config::motion::MotionConfig& k_defaultConfig{config::motion::k_defaultMotionConfig};
class ChassisInputHandlerTest :  public ::testing::TestWithParam<std::tuple<double, double, double, Velocity2D, RPM, Radians>>
{
protected:
    double m_leftJoystickHorizontal{std::get<0>(GetParam())};
    double m_leftJoystickVertical{std::get<1>(GetParam())};
    double m_rightJoystickHorizontal{std::get<2>(GetParam())};

    Velocity2D m_expectedTranslation{std::get<3>(GetParam())};
    RPM m_expectedRPM{std::get<4>(GetParam())};
    Radians m_expectedDisplacement{std::get<5>(GetParam())};

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
    const Velocity2D translationOutput{m_chassisInputHandler.getRemoteTranslation()};
    const RPM rotationOutput{m_chassisInputHandler.getRemoteRotation()};
    const Radians angularDisplacementOutput{m_chassisInputHandler.getRemoteAngularDisplacement()};

    EXPECT_DOUBLE_EQ(translationOutput.x.to<double>(), m_expectedTranslation.x.to<double>());
    EXPECT_DOUBLE_EQ(translationOutput.y.to<double>(), m_expectedTranslation.y.to<double>());
    EXPECT_DOUBLE_EQ(rotationOutput.to<double>(), m_expectedRPM.to<double>());
    EXPECT_DOUBLE_EQ(angularDisplacementOutput.to<double>(), m_expectedDisplacement.to<double>());
}

INSTANTIATE_TEST_SUITE_P(zeroTest, ChassisInputHandlerTest, testing::Values(std::make_tuple(0.0, 0.0, 0.0, Velocity2D{0.0_mps, 0.0_mps}, 0_rpm, 0_rad)));

/*
INSTANTIATE_TEST_SUITE_P(maxTest, ChassisInputHandlerTest,
    testing::Values(std::make_tuple(1.0, 1.0, 1.0, Velocity2D{k_defaultConfig.maxXTranslation, k_defaultConfig.maxYTranslation},
                    k_defaultConfig.maxRotation, k_defaultConfig.maxAngularDisplacement)));
                    */