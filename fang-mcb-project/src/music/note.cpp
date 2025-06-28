#include "note.hpp"
namespace music
{

    Note::Note(Pitch pitch, double beatDuration):
        m_pitch{pitch}, m_beatDuration{beatDuration}
    {
    }

    void Note::play(ISoundMaker& soundMaker)
    {
        soundMaker.playPitch(m_pitch);
    }

    double Note::getBeatDuration() const
    {
        return m_beatDuration;
    }
}