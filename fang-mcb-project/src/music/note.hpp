#ifndef FANG_ROBOTICS_MCB_MUSIC_NOTE_HPP
#define FANG_ROBOTICS_MCB_MUSIC_NOTE_HPP
#include "imusic_element.hpp"
#include "pitch.hpp"
namespace music
{
    class Note : public virtual IMusicElement
    {
    public:
        Note(Pitch pitch, double beatDuration);
        virtual void play(ISoundMaker& soundMaker) override;
        virtual double getBeatDuration() const override;
    private:
        const Pitch m_pitch;
        const double m_beatDuration;
    };
}
#endif