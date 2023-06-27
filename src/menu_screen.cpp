#include "menu_screen.hpp"
#include <iostream>

namespace arkanoid {

MenuScreen::MenuScreen(float a_windowWidth, float a_windowHeight
                    , sf::RectangleShape const a_frame, sf::RenderWindow& a_window)
: m_windowWidth(a_windowWidth)
, m_windowHeight(a_windowHeight)
, m_frame(a_frame)
, m_window(a_window)
, m_play{m_buttonStartX, m_buttonStartY
        , m_buttonWidth, m_buttonHeight
        , sf::Color::Green, WINDOW_OUTLINE, "PLAY", m_fontPlay}
, m_exit{m_buttonStartX, m_buttonStartY + m_buttonHeight + m_spaceBetweenBottons
                , m_buttonWidth, m_buttonHeight
                , sf::Color::Red, WINDOW_OUTLINE, "EXIT", m_fontExit}
, m_gameTitle{"THE ARKANOID GAME", m_fontPlay, 50}
, m_music{}
, m_muter("MUTE - PRESS Q", m_fontPlay, 20)
{
    setTitle();
    setMusic();
    m_muter.setFillColor(sf::Color::Blue);
    m_muter.setPosition(a_windowWidth / 20, a_windowHeight / 40);
}

void MenuScreen::setTitle() noexcept
{
    sf::Color purple{123, 104, 238};
    m_gameTitle.setFillColor(purple);
    m_gameTitle.setStyle(sf::Text::Bold | sf::Text::Underlined | sf::Text::Italic);
    // get the bounds of the text object
    sf::FloatRect textBounds = m_gameTitle.getLocalBounds();
    // set the origin to the center of the text object
    m_gameTitle.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    // set the position of the text object
    m_gameTitle.setPosition(m_windowWidth / 2, m_windowHeight / 5);
}

void MenuScreen::setMusic()
{
    if (!m_music.openFromFile("../arkanoid/audio/opening_screen.wav")) {
        throw std::domain_error("file opening error\n");
    }
    m_music.setVolume(20);
    m_music.setLoop(true);         // make it loop
}

MenuScreen::ExitStatus MenuScreen::run()
{
    ExitStatus status = ExitStatus::CONTINUE;
    m_music.play();
    while (m_window.isOpen()) {
        if((status = flow()) != ExitStatus::CONTINUE) {
            break;
        }
        m_window.display();
    }
    m_music.stop();
    return status;
}

MenuScreen::ExitStatus MenuScreen::flow()
{
    // static int count = 0;
    sf::Event event;
    while(m_window.pollEvent(event)) {
        if(((event.type == sf::Event::KeyPressed)
            && (event.key.code == sf::Keyboard::Escape))
            || (event.type == sf::Event::Closed)) {
            return ExitStatus::EXIT;
        }
        if(event.type == sf::Event::KeyPressed
        && (event.key.code == sf::Keyboard::Q)) {
            //the game is on unmute
            if(m_muter.getString() == "MUTE - PRESS Q") {
                m_muter.setString("UNMUTE - PRESS Q");
                m_music.pause();
            }
            //the game is on mute
            else {
                m_muter.setString("MUTE - PRESS Q");
                m_music.play();
            }
        }
        else if ((event.type == sf::Event::MouseButtonPressed)
                && (event.mouseButton.button == sf::Mouse::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                if(m_play.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return ExitStatus::PLAY;
                }
                else if(m_exit.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return ExitStatus::EXIT;
                }
        }
    }
    m_window.clear();
    m_window.draw(m_frame);
    // ++count;
    m_window.draw(m_gameTitle);
    m_play.drawButton(m_window);
    m_exit.drawButton(m_window);
     m_window.draw(m_muter);
    return ExitStatus::CONTINUE;
}




} //namespace arkanoid
