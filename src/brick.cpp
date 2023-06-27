#include "brick.hpp"

namespace arkanoid {

Brick::Brick(float a_startX, float a_startY, float a_width, float a_height, sf::Color a_color, float a_thickness)
: sf::RectangleShape{sf::Vector2f(a_width - a_thickness, a_height - a_thickness)}
{
    setRectangle(a_startX, a_startY, a_color, a_thickness);
}

void Brick::setRectangle(float a_startX, float a_startY, sf::Color a_color, float a_thickness) noexcept
{
    setPosition(a_startX, a_startY);
    setFillColor(a_color);
    setOutlineColor(sf::Color::Black);
    setOutlineThickness(a_thickness);
}

} // namespace arkanoid
