#pragma once

#include <SFML/Graphics.hpp>
#include <utility>

namespace arkanoid {

class Brick : public sf::RectangleShape {
public:
    explicit Brick(float a_startX, float a_startY, float a_width, float a_height, sf::Color a_color, float a_thickness);
    Brick(const Brick &a_other) = default;
    Brick& operator=(const Brick &a_other) = default;
    ~Brick() = default;

private:
    void setRectangle(float a_startX, float a_startY, sf::Color a_color, float a_thickness) noexcept;

};

} // namespace arkanoid
