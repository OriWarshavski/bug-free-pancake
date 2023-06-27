#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "button.hpp"
#include "screen.hpp"

namespace arkanoid {

class MenuScreen : public Screen {
public:
    explicit MenuScreen(float a_windowWidth, float a_windowHeight
                    , sf::RectangleShape const a_frame, sf::RenderWindow& a_window);
    MenuScreen(const MenuScreen &a_other) = delete;
    MenuScreen& operator=(const MenuScreen &a_other) = delete;
    virtual ~MenuScreen() = default;

    ExitStatus run() override;

private:  
    ExitStatus flow();
    void setTitle() noexcept;
    void setMusic();

private:    
    //details
    static constexpr float WINDOW_OUTLINE = 2;

    float m_windowWidth;
    float m_windowHeight;
    float m_buttonWidth = m_windowWidth / 2;
    float m_buttonHeight = m_windowHeight / 9;
    float m_buttonStartX = m_windowWidth / 4;
    float m_buttonStartY = 3 * m_windowHeight / 9;
    float m_spaceBetweenBottons = m_buttonHeight / 10;
    sf::RectangleShape m_frame;
    sf::RenderWindow& m_window;
    sf::Font m_fontPlay;
    sf::Font m_fontExit;
    Button m_play;
    Button m_exit;
    sf::Text m_gameTitle;
    sf::Music m_music;
    sf::Text m_muter;
};

} // namespace arkanoid
