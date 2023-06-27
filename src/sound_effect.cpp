#include "sound_effect.hpp"

namespace arkanoid {

SoundEffects::SoundEffects()
: m_sounds{}
, m_mute{false}
{
    loadEffects();
}

void SoundEffects::loadEffects()
{
    for(int i = 0; i < maxEffects; ++i) {
        std::string fileName = "../arkanoid/audio/effect-";
        fileName += std::to_string(i);
        fileName += ".wav";
        m_sounds[i].second.loadFromFile(fileName);
        m_sounds[i].first.setBuffer(m_sounds[i].second);

        //setVolume to lost sound
        if(i == static_cast<int>(Types::LOSS)) {
            m_sounds[i].first.setVolume(20);           
        }
        //setVolume to fell sound
        if(i == static_cast<int>(Types::FELL)) {
            m_sounds[i].first.setVolume(20);           
        }
    }
}

void SoundEffects::play(SoundEffects::Types a_effectType) noexcept
{
    if(!m_mute) {
        m_sounds[static_cast<int>(a_effectType)].first.play();
    }
}

void SoundEffects::mute() noexcept
{
    m_mute = true;
}

void SoundEffects::unmute() noexcept
{
    m_mute = false;
}

bool SoundEffects::isMute() const noexcept
{
    return m_mute;
}


} //namespace arkanoid