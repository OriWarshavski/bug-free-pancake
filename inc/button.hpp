#pragma once

#include <SFML/Graphics.hpp>

namespace arkanoid {

class Button : public sf::RectangleShape {
public:
    explicit Button(float a_startX, float a_startY, float a_width, float a_height
                    , sf::Color a_color, float a_thickness
                    , std::string a_text, sf::Font& a_font);
    Button(const Button &a_other);
    Button& operator=(const Button &a_other);
    ~Button() = default;

    void drawButton(sf::RenderWindow& a_window) const;

private:
    void setRectangle(float a_startX, float a_startY, sf::Color a_color, float a_thickness) noexcept;
    void setButtonText(float a_startX, float a_startY, sf::Font& a_font);

private:
    sf::Text m_text;
};

} // namespace arkanoid
