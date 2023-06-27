#include "score.hpp"
#include <iostream>

namespace arkanoid {

Score::Score(float a_startX, float a_startY, sf::Font& a_font)
: sf::Text{"Your score: 0", a_font, 30}
, m_score(0)
, m_startPossition(std::make_pair(a_startX, a_startY))
{
    setScoreText(a_startX, a_startY, a_font);
}

void Score::setScoreText(float a_startX, float a_startY, sf::Font& a_font)
{
    if(!a_font.loadFromFile("fonts/cabin-sketch.bold.ttf")) {
        std::cout << "file error\n";
    }
    setStyle(sf::Text::Bold);
    setFillColor(sf::Color::Blue);
    setPosition(a_startX, a_startY);
}

static std::string buildTextScore(int a_newScore)
{
    std::string text = "Your score: ";
    text += std::to_string(a_newScore);
    return text;
}

void Score::updateScore(int const& a_addToScore) noexcept
{
    m_score += a_addToScore;
    setString(buildTextScore(m_score));
}

void Score::reset() noexcept
{
    m_score = 0;
    setString(buildTextScore(m_score));
}

void Score::winText(float a_startX, float a_startY)
{
    setStyle(sf::Text::Italic);
    setCharacterSize(50);
    setFillColor(sf::Color::Green);
    // auto [x, y] = m_startPossition;
    setPosition(a_startX, a_startY);
    std::string text = "You Win with ";
    text += std::to_string(m_score);
    text += " points !";
    setString(text);
}

int Score::getScore() const noexcept
{
    return m_score;
}

void Score::setScore(int a_score) noexcept
{
    m_score = a_score;
}

} // namespace arkanoid
