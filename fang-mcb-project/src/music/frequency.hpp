#ifndef FANG_ROBOTICS_MCB_MUSIC_FREQUENCY_HPP
#define FANG_ROBOTICS_MCB_MUSIC_FREQUENCY_HPP
#include "unitaliases.hpp"
#include "pitch.hpp"

namespace music
{
    extern const Hertz k_A5StandardFrequency;
    constexpr Hertz pitchToFrequency(Pitch pitch);
}
#endif