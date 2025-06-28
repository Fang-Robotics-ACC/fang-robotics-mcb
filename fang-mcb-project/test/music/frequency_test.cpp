#include <gtest/gtest.h>
#include "music/frequency.hpp"

namespace music
{
    TEST(pitchToFrequency, homePitch)
    {
        //There should be no shenanigans
        const Hertz expected{k_A4StandardFrequency};
        const Hertz output{pitchToFrequency(Pitch::A4)};
        EXPECT_DOUBLE_EQ(expected.to<double>(), output.to<double>());
    }

    TEST(pitchToFrequency, octaveUp)
    {
        //There should be no shenanigans
        const Hertz expected{k_A4StandardFrequency * 2};
        const Hertz output{pitchToFrequency(Pitch::A5)};
        EXPECT_DOUBLE_EQ(expected.to<double>(), output.to<double>());
    }

    TEST(pitchToFrequency, octaveDown)
    {
        //There should be no shenanigans
        const Hertz expected{k_A4StandardFrequency * 0.5};
        const Hertz output{pitchToFrequency(Pitch::A3)};
        EXPECT_DOUBLE_EQ(expected.to<double>(), output.to<double>());
    }
}