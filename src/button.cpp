#include "button.hpp"
#include <iostream>

namespace arkanoid {

Button::Button(float a_startX, float a_startY, float a_width, float a_height
                    , sf::Color a_color, float a_thickness
                    , std::string a_text, sf::Font& a_font)
: sf::RectangleShape{sf::Vector2f(a_width, a_height)}
, m_text{a_text, a_font, 30}
{
    setRectangle(a_startX, a_startY, a_color, a_thickness);
    setButtonText(a_startX + a_width / 2, a_startY + a_height / 2, a_font);
}

Button::Button(const Button &a_other)
: sf::RectangleShape(a_other)
, m_text(a_other.m_text)
{
}

void Button::setRectangle(float a_startX, float a_startY, sf::Color a_color, float a_thickness) noexcept
{
    setPosition(a_startX, a_startY);
    setFillColor(a_color);
    setOutlineColor(sf::Color::Blue);
    setOutlineThickness(a_thickness);
}

void Button::setButtonText(float a_startX, float a_startY, sf::Font& a_font)
{
    if(!a_font.loadFromFile("fonts/cabin-sketch.bold.ttf")) {
        std::cout << "file error\n";
    }
    m_text.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = m_text.getLocalBounds(); 
    m_text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    m_text.setPosition(a_startX, a_startY);
}

Button& Button::operator=(const Button &a_other)
{
    setPosition(a_other.getPosition());
    setSize(a_other.getSize());
    m_text = a_other.m_text;
    return *this;
}

void Button::drawButton(sf::RenderWindow& a_window) const 
{
    a_window.draw(*this);
    a_window.draw(m_text);

}

} // namespace arkanoid
