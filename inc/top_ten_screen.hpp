#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <utility>
#include <tuple>
#include <string>
#include <fstream>

#include "button.hpp"
#include "screen.hpp"
#include "player.hpp"

namespace arkanoid {

using Name = std::string;
struct PlayerResult {
    PlayerResult(int a_points, float a_time); //ctor

    int m_points;
    float m_timeMilli;
};

bool operator<(const PlayerResult& a_first, const PlayerResult& a_second);

class TopTenScreen : public Screen {
public:
    explicit TopTenScreen(float a_windowWidth, float a_windowHeight
                    , sf::RenderWindow& a_window, std::string const a_fileName);
    TopTenScreen(const TopTenScreen &a_other) = delete;
    TopTenScreen& operator=(const TopTenScreen &a_other) = delete;
    virtual ~TopTenScreen() = default;

    ExitStatus run() override;
    void addPlayerToTable(std::string a_name, int const& a_score, float const& a_time);
    bool isPlayerInTopTen(int const& a_score, float const& a_time) noexcept;

private:
    void setFrame() noexcept;
    void setTexts(float a_windowWidth, float a_windowHeight);
	void refresh();
    TopTenScreen::ExitStatus flow();
    void save() const;
    void load();
    void fixStringToSize(std::string& a_string, size_t a_size) const noexcept;


private:
    static constexpr float FRAME_OUTLINE = 2;
    static constexpr float SPACE_SCORE_NAME = 30;
    static constexpr float SPACE_IN_TABLE = 200;

    sf::Font m_font;
    sf::Text m_text;
    sf::RenderWindow& m_window;
	std::multimap<PlayerResult, Name, std::function<bool(PlayerResult, PlayerResult)>> m_topTenScores;
    sf::RectangleShape m_frame;
    std::string const m_fileName;
    sf::Text m_title;
};

} // namespace arkanoid01
