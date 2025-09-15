#include <gtest/gtest.h>

#include "control/turret/proxy_turret_input.hpp"
namespace fang::turret::proxyTurretInputTest
{
    struct InputState 
    {
        double pitch;
        double yaw;
    };

    struct MatchTestParam
    {
        ProxyTurretInput::Config config;
        InputState input;
        InputState expected;
    };

    class MatchTest : public testing::TestWithParam<MatchTestParam>
    {
    public:
        MatchTest() {}
    protected:
        const ProxyTurretInput::Config kProxyConfig_{GetParam().config};
        const InputState kInput_{GetParam().input};
        const InputState kExpected_{GetParam().expected};

        ProxyTurretInput proxyInput_{kProxyConfig_};
    };

    /**
     * This makes sure that the values being passed from setter
     * to getter are matching
     */
    TEST_P(MatchTest, basicMatching)
    {
        proxyInput_.setPitch(kInput_.pitch);
        proxyInput_.setYaw(kInput_.yaw);

        EXPECT_DOUBLE_EQ(proxyInput_.getPitch(), kExpected_.pitch);
        EXPECT_DOUBLE_EQ(proxyInput_.getYaw(), kExpected_.yaw);
    }

    INSTANTIATE_TEST_CASE_P
    (
        zero,
        MatchTest,
        testing::Values
        (
            MatchTestParam
            {
                .config = 
                ProxyTurretInput::Config
                {
                    .pitchScale = 1.0,
                    .yawScale = 1.0
                },
                .input =
                InputState
                {
                    .pitch = 0.0,
                    .yaw = 0.0
                },
                .expected =
                InputState
                {
                    .pitch = 0.0,
                    .yaw = 0.0
                }
            }
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        postiveMatch,
        MatchTest,
        testing::Values
        (
            MatchTestParam
            {
                .config = 
                ProxyTurretInput::Config
                {
                    .pitchScale = 1.0,
                    .yawScale = 1.0
                },
                .input =
                InputState
                {
                    .pitch = 1.0,
                    .yaw = 1.0
                },
                .expected =
                InputState
                {
                    .pitch = 1.0,
                    .yaw = 1.0
                }
            },
            MatchTestParam
            {
                .config = 
                ProxyTurretInput::Config
                {
                    .pitchScale = 1.0,
                    .yawScale = 1.0
                },
                .input =
                InputState
                {
                    .pitch = 345345.23432,
                    .yaw = 34534.3453450
                },
                .expected =
                InputState
                {
                    .pitch = 345345.23432,
                    .yaw = 34534.3453450
                }
            }
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        negativeMatch,
        MatchTest,
        testing::Values
        (
            MatchTestParam
            {
                .config = 
                ProxyTurretInput::Config
                {
                    .pitchScale = 1.0,
                    .yawScale = 1.0
                },
                .input =
                InputState
                {
                    .pitch = -1.0,
                    .yaw = -1.0
                },
                .expected =
                InputState
                {
                    .pitch = -1.0,
                    .yaw = -1.0
                }
            },
            MatchTestParam
            {
                .config = 
                ProxyTurretInput::Config
                {
                    .pitchScale = 1.0,
                    .yawScale = 1.0
                },
                .input =
                InputState
                {
                    .pitch = -345345.23432,
                    .yaw = -34534.3453450
                },
                .expected =
                InputState
                {
                    .pitch = -345345.23432,
                    .yaw = -34534.3453450
                }
            }
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        mixedMatch,
        MatchTest,
        testing::Values
        (
            MatchTestParam
            {
                .config = 
                ProxyTurretInput::Config
                {
                    .pitchScale = 1.0,
                    .yawScale = 1.0
                },
                .input =
                InputState
                {
                    .pitch = 1.0,
                    .yaw = 1.0
                },
                .expected =
                InputState
                {
                    .pitch = 1.0,
                    .yaw = 1.0
                }
            },
            MatchTestParam
            {
                .config = 
                ProxyTurretInput::Config
                {
                    .pitchScale = 1.0,
                    .yawScale = 1.0
                },
                .input =
                InputState
                {
                    .pitch = 345345.23432,
                    .yaw = -34534.3453450
                },
                .expected =
                InputState
                {
                    .pitch = 345345.23432,
                    .yaw = -34534.3453450
                }
            }
        )
    );

    INSTANTIATE_TEST_CASE_P
    (
        scalingMatch,
        MatchTest,
        testing::Values
        (
            MatchTestParam
            {
                .config = 
                ProxyTurretInput::Config
                {
                    .pitchScale = 32.0,
                    .yawScale = 234.0
                },
                .input =
                InputState
                {
                    .pitch = 1.0,
                    .yaw = 1.0
                },
                .expected =
                InputState
                {
                    .pitch = 32.0,
                    .yaw = 234.0
                }
            },
            MatchTestParam
            {
                .config = 
                ProxyTurretInput::Config
                {
                    .pitchScale = 0.34534,
                    .yawScale = 0.345345
                },
                .input =
                InputState
                {
                    .pitch = 1.0,
                    .yaw = 1.0 
                },
                .expected =
                InputState
                {
                    .pitch = 0.34534,
                    .yaw = 0.345345
                }
            }
        )
    );
}