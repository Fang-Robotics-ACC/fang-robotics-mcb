#ifndef FANG_ROBOTICS_MCB_MUSIC_ELEMENT_HPP
#define FANG_ROBOTICS_MCB_MUSIC_ELEMENT_HPP
#include "pitch.hpp"
#include "isound_maker.hpp"
namespace music
{
    class IMusicElement
    {
    public:
        virtual void play(ISoundMaker& soundMaker) = 0;
        virtual double getBeatDuration() = 0;
    };
}
#endif