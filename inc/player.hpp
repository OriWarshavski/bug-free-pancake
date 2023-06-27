#pragma once

#include <SFML/Graphics.hpp>
#include "score.hpp"
#include "live.hpp"
#include "clock.hpp"

namespace arkanoid {

class Player {
public:
    explicit Player(float a_scoreStartX, float a_scoreStartY
                    , float a_livesStartX, float a_livesStartY
                    , float a_clockX, float a_clockY);
    Player(const Player &a_other) = delete;
    Player& operator=(const Player &a_other) = delete;
    ~Player() = default;    

    const int lives() const noexcept;
    void liveReduce() noexcept;
    Score getScoreText() const noexcept;
    void addPoints(int const& a_pointToAdd) noexcept;
    Lives getLives() const noexcept;
    void winning(float a_startX, float a_startY);
    void reset() noexcept;
    int score() const noexcept;
    float time() const noexcept;
    void startTimeCount() noexcept;
    void draw(sf::RenderWindow& a_window) noexcept;
    void mute() noexcept;
    void unmute() noexcept;

private:
    sf::Font m_fontScore;
    sf::Font m_fontLives;
    Score m_score;
    Lives m_lives;
    Clock m_clock;
    sf::Text m_muter;
};

} // namespace arkanoid
