#include "ball.hpp"


namespace arkanoid {

static sf::CircleShape createCircle(const float a_radius
                , const float a_thikness, const sf::Color a_fill, const sf::Color a_outLine
                , float a_startX, float a_startY)
{
    sf::CircleShape circle(a_radius);
    sf::Color aque{127, 255 ,212};
    sf::Color purpleS{123,104,238};
    circle.setFillColor(aque);
    circle.setOutlineColor(purpleS);
    circle.setOutlineThickness(a_thikness);
    circle.setPosition(a_startX, a_startY);
    return circle;
}

Ball::Ball(float a_startX, float a_startY, float a_radius, float a_outline)
: sf::CircleShape(createCircle(a_radius, a_outline, sf::Color::Black
                                ,sf::Color::Blue ,a_startX, a_startY))
, m_startPossition(std::make_pair(a_startX, a_startY))
{
}

void Ball::move(float a_offsetX, float offsetY) noexcept
{
    sf::Vector2f pos = getPosition();
    m_velocity.first = a_offsetX;
    m_velocity.second = offsetY;
    setPosition(pos.x + a_offsetX, pos.y + offsetY);
}

void Ball::move() noexcept
{
    sf::Vector2f pos = getPosition();
    setPosition(pos.x + m_velocity.first, pos.y + m_velocity.second);
}

std::pair<float, float> Ball::velocityCopy() const noexcept
{
    return m_velocity;
}

void Ball::moveRight(float a_velocity) noexcept 
{
    sf::Vector2f pos = getPosition();
    setPosition(pos.x + a_velocity, pos.y);
}

void Ball::moveLeft(float a_velocity) noexcept
{   
    sf::Vector2f pos = getPosition();
    setPosition(pos.x - a_velocity, pos.y);
}

void Ball::resetPosition() noexcept
{
    auto const [startX, startY] = m_startPossition;
    setPosition(startX, startY);
}

} // namespace arkanoid01

