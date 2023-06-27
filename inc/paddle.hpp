#pragma once

#include <SFML/Graphics.hpp>
#include <utility>

namespace arkanoid {

class Paddle : public sf::RectangleShape {
public:
    explicit Paddle(float a_startX, float a_startY, float a_width, float a_height, float a_outline);
    Paddle(const Paddle &a_other) = default;
    Paddle& operator=(const Paddle &a_other) = default;
    ~Paddle() = default;    

    void moveRight() noexcept;
    void moveLeft() noexcept;
    float velocityCopy() const noexcept;
    void resetPosition() noexcept;

private:
    void setRectangle(float a_startX, float a_startY, float a_outline) noexcept;

private:
    float m_velocity = 30;
    std::pair<float, float> m_startPossition;
};

} // namespace arkanoid
