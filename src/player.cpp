#include "player.hpp"

namespace arkanoid {

Player::Player(float a_scoreStartX, float a_scoreStartY
                    , float a_livesStartX, float a_livesStartY
                    , float a_clockX, float a_clockY)
: m_score(a_scoreStartX, a_scoreStartY, m_fontScore)
, m_lives(a_livesStartX, a_livesStartY, m_fontLives)
, m_clock(a_clockX, a_clockY)
, m_muter("MUTE - PRESS Q", m_fontScore, 20)
{
    m_muter.setFillColor(sf::Color::Blue);
    m_muter.setPosition(a_scoreStartX, a_scoreStartY / 2);
}

const int Player::lives() const noexcept
{
    return m_lives.howMuch();
}

void Player::liveReduce() noexcept
{
    m_lives.updateLives(-1);
}

Score Player::getScoreText() const noexcept
{
    return m_score;
}

void Player::addPoints(int const& a_pointToAdd) noexcept
{
    m_score.updateScore(a_pointToAdd);
}

Lives Player::getLives() const noexcept
{
    return m_lives;
}

void Player::winning(float a_startX, float a_startY)
{
    m_score.winText(a_startX, a_startY);
}

void Player::reset() noexcept 
{
    m_score.reset();
    m_lives.reset();
    m_clock.reset();
}

int Player::score() const noexcept
{
    return m_score.getScore();
}

float Player::time() const noexcept
{
    return m_clock.getTime();
}

void Player::startTimeCount() noexcept
{
    m_clock.reset();
}

void Player::draw(sf::RenderWindow& a_window) noexcept
{
    a_window.draw(m_score);
    a_window.draw(m_lives);
    m_clock.drawClock(a_window);
    a_window.draw(m_muter);
}

void Player::mute() noexcept
{
    m_muter.setString("UNMUTE - PRESS Q");
}

void Player::unmute() noexcept
{
    m_muter.setString("MUTE - PRESS Q");
}

} // namespace arkanoid
