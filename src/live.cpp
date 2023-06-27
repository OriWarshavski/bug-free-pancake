#include "live.hpp"
#include <iostream>

namespace arkanoid {

Lives::Lives(float a_startX, float a_startY, sf::Font& a_font)
: sf::Text{}
{
    createLivesText(a_startX, a_startY, a_font);
}

void Lives::createLivesText(float a_startX, float a_startY, sf::Font& a_font)
{
    if(!a_font.loadFromFile("fonts/HEART shapes.ttf")) {
        std::cout << "file error\n";
    }
    setFont(a_font);
    setStyle(sf::Text::Bold);
    setString("U  U  U");
    setCharacterSize(30);
    setFillColor(sf::Color::Red);
    setPosition(a_startX, a_startY);
}

static std::string buildTextLives(int a_livesNumber)
{
    std::string text = "";
    for(int i = 0; i < a_livesNumber; ++i) {
        text += "U";
        if(i < a_livesNumber - 1) {
            text += "  ";
        }
    }
    return text;
}

void Lives::updateLives(int a_livesToAdd) noexcept
{
    m_livesNumber += a_livesToAdd;
    assert(m_livesNumber >= 0);
    setString(buildTextLives(m_livesNumber));
}

int const& Lives::howMuch() const noexcept
{
    return m_livesNumber;
}

void Lives::reset() noexcept
{
    m_livesNumber = 3;
    setString(buildTextLives(m_livesNumber));
}

} // namespace arkanoid
