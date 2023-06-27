#pragma once

#include <SFML/Audio.hpp>
#include <utility>

namespace arkanoid {

class SoundEffects {
public:
    enum class Types {BREAK = 0, LOSS = 1, IN_TOP_10 = 2, WIN = 3, 
                        BALL_SOLID = 4, FELL = 5};

    SoundEffects(); 
    SoundEffects(const SoundEffects &a_other) = delete;
    SoundEffects& operator=(const SoundEffects &a_other) = delete;
    ~SoundEffects() = default;

    void play(SoundEffects::Types a_effectType) noexcept;

    void mute() noexcept;
    void unmute() noexcept;
    bool isMute() const noexcept;


private:
    void loadEffects();

private:
    static constexpr int maxEffects = 6;


    std::pair<sf::Sound, sf::SoundBuffer> m_sounds[maxEffects];
    bool m_mute;
};




} // namespace arkanoid
