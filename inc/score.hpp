#pragma once

#include <SFML/Graphics.hpp>
#include <utility>

namespace arkanoid {

class Score : public sf::Text {
public:
    explicit Score(float a_startX, float a_startY, sf::Font& a_font);
    Score(const Score &a_other) = default;
    Score& operator=(const Score &a_other) = default;
    ~Score() = default;

    void updateScore(int const& a_addToScore) noexcept;
    void winText(float a_startX, float a_startY);
    void reset() noexcept;
    int getScore() const noexcept;
    void setScore(int a_score) noexcept;

private:
    void setScoreText(float a_startX, float a_startY, sf::Font& a_font);

private:
    int m_score;
    std::pair<float, float> m_startPossition;
};

} // namespace arkanoid
