#pragma once

#include <SFML/Graphics.hpp>

namespace arkanoid {

class Lives : public sf::Text {
public:
    explicit Lives(float a_startX, float a_startY, sf::Font& a_font);
    Lives(const Lives &a_other) = default;
    Lives& operator=(const Lives &a_other) = default;
    ~Lives() = default;

    void updateLives(int a_livesToAdd) noexcept;
    int const& howMuch() const noexcept;
    void reset() noexcept;

private:
void createLivesText(float a_startX, float a_startY, sf::Font& a_font);

private:
    int m_livesNumber = 3;
};

} // namespace arkanoid
