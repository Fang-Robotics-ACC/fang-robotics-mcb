#ifndef FANG_ROBOTICS_MCB_I_SOUND_MAKER_HPP
#define FANG_ROBOTICS_MCB_I_SOUND_MAKER_HPP
#include "pitch.hpp"
namespace music
{
    class ISoundMaker
    {
        virtual void playPitch(Pitch pitch) = 0;
        virtual void mute() = 0;
    };
}
#endif