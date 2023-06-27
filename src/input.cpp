#include "input.hpp"

namespace arkanoid {

Input::Input(sf::RenderWindow& a_window)
: m_window(a_window)
, m_font{}
, m_frame{}
, m_text{"Congrats!\n Your score is in the top ten!\n\n Type Your Name:\n", m_font, 30}
, m_textBox{}
{
    sf::Vector2f windowSize(a_window.getSize());
    m_windowWidth = windowSize.x;
    m_windowHeight = windowSize.y;
    setFrame();

	if(!m_font.loadFromFile("../arkanoid/fonts/cabin-sketch.bold.ttf")) {
        throw std::domain_error("file error\n");
    }
    sf::Color darkRed(128, 0, 0);
	m_text.setFillColor(darkRed);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setPosition(m_windowWidth / 4, m_windowHeight / 3);
    setTextBox();
}

void Input::setFrame() noexcept
{   
    m_frame.setSize(sf::Vector2f(m_windowWidth - 2 * FRAME_THICKNESS, m_windowHeight - 2 * FRAME_THICKNESS));
    m_frame.setPosition(FRAME_THICKNESS, FRAME_THICKNESS);
    m_frame.setOutlineColor(sf::Color::Green);
    sf::Color turqoise{175, 238, 238};
    m_frame.setFillColor(turqoise);
    m_frame.setOutlineThickness(FRAME_THICKNESS);
}

void Input::setTextBox() noexcept
{   
    sf::FloatRect textBounds = m_text.getLocalBounds();

    // Create a rectangle shape with the size of the text
    m_textBox.setSize(sf::Vector2f(textBounds.width + TEXT_BOX_BLANK, textBounds.height + TEXT_BOX_BLANK));
    
    sf::Color translucentYellow(255, 255, 0, 128);

    m_textBox.setFillColor(translucentYellow);
    m_textBox.setOutlineThickness(FRAME_THICKNESS);
    m_textBox.setOutlineColor(sf::Color::Black);
    m_textBox.setPosition(m_text.getPosition() - sf::Vector2f(5, 5));
}

std::string Input::typeYourName() noexcept
{
    sf::Event event;
    bool exit = false;
    std::string name;
    while (!exit) {
        while(m_window.pollEvent(event)) {
            if(event.type == sf::Event::TextEntered) {
                if(event.text.unicode < 128 && event.text.unicode != '\b') {
                    if (event.text.unicode == '\r' 
                    || event.text.unicode == '\n') {
                        m_text.setString("Congrats!\n Your score is in the top ten!\n\n Type Your Name:\n");
                        exit = true;
                        break;
                    }
                    sf::Text nameTempText{name, m_font, 30};
                    sf::FloatRect textBounds = nameTempText.getLocalBounds();
                    if(textBounds.width < 190) {
                        m_text.setString(m_text.getString() + static_cast<char>(event.text.unicode));
                        name += static_cast<char>(event.text.unicode);
                    }
                }
            }
            else if(event.type == sf::Event::KeyPressed 
            && event.key.code == sf::Keyboard::Backspace
            && !name.empty()) {
                name.erase(name.size() - 1);
                std::string currentString = m_text.getString();
                currentString.erase(currentString.size() - 1);
                m_text.setString(currentString);
            }

            if(((event.type == sf::Event::KeyPressed) 
            && (event.key.code == sf::Keyboard::Escape))) {
                exit = true;
                break;
            }
            if(event.type == sf::Event::Closed) {
                exit = true;
                m_window.close();
                break;
            }
        }
        m_window.clear();
        m_window.draw(m_frame);
        m_window.draw(m_textBox);
        m_window.draw(m_text);
        m_window.display();
    }
    
    return name;
}

} //namespace arkanoid