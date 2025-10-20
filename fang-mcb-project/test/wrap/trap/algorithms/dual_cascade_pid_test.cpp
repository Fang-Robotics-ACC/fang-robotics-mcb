#include "wrap/trap/algorithms/smooth_pid.hpp"
#include "wrap/trap/algorithms/dual_cascade_pid.hpp"
#include <gmock/gmock.h>


namespace trap::algorithms::dualCascadePidTest
{
    using DoubleDualSmoothPid = DualCascadePid<double, double, double, double>;
    using DoubleSmoothPid = SmoothPid<double, double, double>;
    struct MatchTestParam 
    {
        double mainTarget;
        double mainCurrent;
        double intermediateCurrent;
        double deltaTime;
        DoubleDualSmoothPid::Config config;
        double mainErrorDerivative = 0.0;
        double intermediateErrorDerivative = 0.0;
    };

    //Sets up for manually calculating a cascade pid
    //and comparing if DualSmoothPid returns the same results
    //
    class MatchTest : testing::TestWithParam<MatchTestParam>
    {
    protected:
        const MatchTestParam& kParam{GetParam()};
        const double kMainTarget{kParam.mainTarget};
        const double kMainCurrent{kParam.mainCurrent};
        const double kIntermediateCurrent{kParam.intermediateCurrent};
        const double kDeltaTime{kParam.deltaTime};
        const DoubleDualSmoothPid::Config kConfig{kParam.config};
        const double kMainErrorDerivative{kParam.mainErrorDerivative};
        const double kIntermediateErrorDerivative{kParam.intermediateErrorDerivative};

        DoubleDualSmoothPid dualPid{kConfig};
        DoubleSmoothPid mainPid{kConfig.mainPidConfig};
        DoubleSmoothPid intermediatePid{kConfig.intermediatePidConfig};
    };

    TEST_P(MatchTest, generalMatching)
    {
        // DualSmoothPid needs a means to check the internals
        // Or a means independent of time
    }

    TEST(dualSmoothPid, compilationTest)
    {
        constexpr DoubleDualSmoothPid::IntermediatePid::Config kGeneralPidConfig
        {
            .kp = 1.0,
            .ki = 23.3,
            .kd = 14.0
        };

        constexpr DoubleDualSmoothPid::Config kConfig
        {
            .mainPidConfig = kGeneralPidConfig,
            .intermediatePidConfig = kGeneralPidConfig,
            .mainPidInitialValue = 0.0,
            .intermediatePidInitialValue = 0.0
        };

        DoubleDualSmoothPid pid{kConfig};
    }
}