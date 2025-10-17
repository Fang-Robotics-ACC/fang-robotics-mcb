#include "wrap/trap/algorithms/smooth_pid.hpp"
#include "wrap/trap/algorithms/dual_smooth_pid.hpp"
#include <gmock/gmock.h>


namespace trap::algorithms::dualSmoothPidTest
{
    using DoubleDualSmoothPid = DualSmoothPid<double, double, double, double>;
    using DoubleSmoothPid = SmoothPid<double, double, double>;
    struct MatchTestParam 
    {
        double mainTarget;
        double mainCurrent;
        double intermediateCurrent;
        double deltaTime;
        DoubleDualSmoothPid::Config config;
    };

    /**
     * Sets up for manually calculating a cascade pid
     * and comparing if DualSmoothPid returns the same results
     */
    class MatchTest : testing::TestWithParam<MatchTestParam>
    {
    protected:
        const MatchTestParam& kParam{GetParam()};
        const double kMainTarget{kParam.mainTarget};
        const double kMainCurrent{kParam.mainCurrent};
        const double kIntermediateCurrent{kParam.intermediateCurrent};
        const double kDeltaTime{kParam.deltaTime};
        const DoubleDualSmoothPid::Config kConfig{kParam.config};

        DoubleDualSmoothPid dualPid{kConfig};
        DoubleSmoothPid mainPid{kConfig.mainPidConfig};
        DoubleSmoothPid intermediatePid{kConfig.intermediatePidConfig};
    };

}