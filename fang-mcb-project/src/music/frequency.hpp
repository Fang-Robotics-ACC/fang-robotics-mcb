#ifndef FANG_ROBOTICS_MCB_MUSIC_FREQUENCY_HPP
#define FANG_ROBOTICS_MCB_MUSIC_FREQUENCY_HPP
#include "unitaliases.hpp"
#include "pitch.hpp"

namespace music
{
    static constexpr Hertz k_A4StandardFrequency{440};
    Hertz pitchToFrequency(Pitch pitch);
}
#endif