#pragma once

#include <SFML/Graphics.hpp>

namespace arkanoid {

class Clock : public sf::Text {
public:
    explicit Clock(float a_startX, float a_startY);
    Clock(const Clock &a_other) = default;
    Clock& operator=(const Clock &a_other) = default;
    ~Clock() = default;

    void reset() noexcept;
    void drawClock(sf::RenderWindow& a_window) noexcept;
    float getTime() const noexcept;
    static std::string formatElapsedTime(long elapsedMillis) noexcept;


private:
    sf::Clock m_clock;
    sf::Font m_font;
};

} // namespace arkanoid
