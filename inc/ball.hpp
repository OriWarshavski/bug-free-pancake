#pragma once

#include <SFML/Graphics.hpp>
#include <utility>

namespace arkanoid {

class Ball : public sf::CircleShape {
public:
    explicit Ball(float a_startX, float a_startY, float a_radius, float a_outline);
    Ball(const Ball &a_other) = default;
    Ball& operator=(const Ball &a_other) = default;
    ~Ball() = default;

    void move(float a_offsetX, float offsetY) noexcept;
    void move() noexcept;
    std::pair<float, float> velocityCopy() const noexcept;
    void moveRight(float a_velocity) noexcept;
    void moveLeft(float a_velocity) noexcept;
    void resetPosition() noexcept;

private:
    sf::Sprite createSprite();

    std::pair<float, float> m_velocity = std::make_pair(6, -6);
    sf::Color m_fill = sf::Color::Black;
    sf::Color m_outLine = sf::Color::Blue;

    sf::Sprite m_sprite;
    std::pair<float, float> m_startPossition;
};

} // namespace arkanoid
