#include "paddle.hpp"

namespace arkanoid {

Paddle::Paddle(float a_startX, float a_startY, float a_width, float a_height, float a_outline)
: sf::RectangleShape{sf::Vector2f(a_width, a_height)}
, m_startPossition(std::make_pair(a_startX, a_startY))
{
    setRectangle(a_startX, a_startY, a_outline);
}

void Paddle::setRectangle(float a_startX, float a_startY, float a_outline) noexcept
{
    setPosition(a_startX, a_startY);
    sf::Color lightBlue{200, 250 ,250};
    sf::Color purpleS{123,104,238};
    setFillColor(lightBlue);
    setOutlineColor(purpleS);
    setOutlineThickness(a_outline);
}

void Paddle::moveRight() noexcept 
{
    sf::Vector2f pos = getPosition();
    setPosition(pos.x + m_velocity, pos.y);
}

void Paddle::moveLeft() noexcept
{
    sf::Vector2f pos = getPosition();
    setPosition(pos.x - m_velocity, pos.y);
}

float Paddle::velocityCopy() const noexcept
{
    return m_velocity;
}

void Paddle::resetPosition() noexcept
{
    auto const [startX, startY] = m_startPossition;
    setPosition(startX, startY);
}

} // namespace arkanoid
