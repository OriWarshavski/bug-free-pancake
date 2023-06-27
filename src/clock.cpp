#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "clock.hpp"

namespace arkanoid {

Clock::Clock(float a_startX, float a_startY)
: m_clock{}
, m_font{}
{
    if(!m_font.loadFromFile("../arkanoid/fonts/cabin-sketch.bold.ttf")) {
        throw std::domain_error("file error\n");
    }
    setFont(m_font);
    setString(std::to_string(m_clock.getElapsedTime().asMilliseconds()));
    setCharacterSize(20);
    setFillColor(sf::Color::Black);
    // get the bounds of the text object
    sf::FloatRect textBounds = getLocalBounds();
    // set the origin to the center of the text object
    setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    // set the position of the text object
    setPosition(a_startX, a_startY);
}

std::string Clock::formatElapsedTime(long elapsedMillis) noexcept {
    int minutes = (elapsedMillis % 3600000) / 60000; // 1 minute = 60000 milliseconds
    int seconds = (elapsedMillis % 60000) / 1000;
    //int milliseconds = elapsedMillis % 1000;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes << ":" 
      << std::setfill('0') << std::setw(2) << seconds;
      //<< std::setfill('0') << std::setw(2) << milliseconds;
      return oss.str();
}

void Clock::reset() noexcept
{
    m_clock.restart();
    setString(formatElapsedTime(m_clock.getElapsedTime().asMilliseconds()));
}

void Clock::drawClock(sf::RenderWindow& a_window) noexcept
{
    setString(formatElapsedTime(m_clock.getElapsedTime().asMilliseconds()));
    a_window.draw(*this);
}

float Clock::getTime() const noexcept
{
    return m_clock.getElapsedTime().asMilliseconds();
}

} // namespace arkanoid
