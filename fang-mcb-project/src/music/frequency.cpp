#include "frequency.hpp"
namespace music
{
    const Hertz k_A5StandardFrequency{440};

    //In order to go up an octave a frequency must be doubled
    //So in Equal Temperament, there are 12 notes per octave
    //that are evenly spaced
    //thus, since we mudst multiply to move up or down a pitch
    //we need to multiply by a constant 12 times, which must result
    //in 2 in order to have 12 notes per octave
    //  "Why It's Impossible to Tune a Piano" by MinutePhysics
    // https://www.youtube.com/watch?v=1Hqm0dYKUx4
    constexpr double k_octaveRootPower{1.0 / 12.0};

    //Frequencies move up or down an octave by multiplying or dividingf by 2
    constexpr double k_octaveMultiplier{2.0};

    /// @brief The ratio between two frequencies a half step apart
    const double k_chromaticRatio{std::pow(k_octaveMultiplier, k_octaveRootPower)};

    const

    //General formula
    constexpr Hertz pitchToFrequencyBase(Pitch pitch, Hertz baseFrequency, int basePitchMidiIndex)
    {
        //This was pretty easy to derive
        const int k_rawPitch{static_cast<int>(pitch)};
        const int k_halfSteps{k_rawPitch - basePitchMidiIndex};
        return baseFrequency * std::pow(k_chromaticRatio, k_halfSteps);

    }

    constexpr Hertz pitchToFrequency(Pitch pitch)
    {
        constexpr int k_A5MidiIndex{static_cast<int>(Pitch::A5)};
        return pitchToFrequencyBase(pitch, k_A5StandardFrequency, k_A5MidiIndex);
    }
}