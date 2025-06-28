#ifndef FANG_ROBOTICS_MCB_MUSIC_REST_HPP
#define FANG_ROBOTICS_MCB_MUSIC_REST_HPP
#include "imusic_element.hpp"
namespace music
{
    class Rest : public virtual IMusicElement
    {
    public:
        Rest(double beatDuration);
        virtual void play(ISoundMaker& soundMaker) override;
        virtual double getBeatDuration() const override;
    private:
        const double m_beatDuration;
    };
}
#endif