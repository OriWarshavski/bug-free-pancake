#pragma once

#include <SFML/Graphics.hpp>

namespace arkanoid {

class Input {
public:
    explicit Input(sf::RenderWindow& a_window);
    Input(const Input &a_other) = delete;
    Input& operator=(const Input &a_other) = delete;
    ~Input() = default;

    std::string typeYourName() noexcept;

private:
    void setFrame() noexcept;
    void setTextBox() noexcept;

private:
    static constexpr int FRAME_THICKNESS = 4;
    static constexpr int TEXT_BOX_BLANK = 20;

    sf::RenderWindow& m_window;
    int m_windowWidth;
    int m_windowHeight;
    sf::Font m_font;
    sf::RectangleShape m_frame;
    sf::Text m_text;
    sf::RectangleShape m_textBox;


};

} // namespace arkanoid
