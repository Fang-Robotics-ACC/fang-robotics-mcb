#include "rest.hpp"
namespace music
{

    Rest::Rest(double beatDuration):
        m_beatDuration{beatDuration}
    {
    }

    void Rest::play(ISoundMaker& soundMaker)
    {
        soundMaker.mute();
    }

    double Rest::getBeatDuration() const
    {
        return m_beatDuration;
    }
}