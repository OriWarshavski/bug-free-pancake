#include <iostream>
#include <sstream>
#include <iomanip>

#include "top_ten_screen.hpp"
#include "clock.hpp"

namespace arkanoid {

PlayerResult::PlayerResult(int a_points, float a_time)
: m_points(a_points)
, m_timeMilli(a_time)
{
}

bool operator<(const PlayerResult& a_first, const PlayerResult& a_second) {
    // Compare scores first
    if (a_first.m_points != a_second.m_points) {
        return a_first.m_points > a_second.m_points; // bigger score comes first
    } 
    else {
        return a_first.m_timeMilli < a_second.m_timeMilli; // smaller time comes first
    }
}

TopTenScreen::TopTenScreen(float a_windowWidth, float a_windowHeight
                    , sf::RenderWindow& a_window, std::string const a_fileName)
: m_font{}
, m_text{"NAME             SCORE               MINUTS", m_font, 30}
, m_window{a_window}
, m_topTenScores {
        [](PlayerResult a_first, PlayerResult a_second) {
            return a_first < a_second; }}
, m_frame{sf::Vector2f(a_windowWidth - FRAME_OUTLINE * 2, a_windowHeight - FRAME_OUTLINE * 2)}
, m_fileName{a_fileName}
, m_title{"TOP 10 TABLE", m_font, 40}
{
    setFrame();
    setTexts(a_windowWidth, a_windowHeight);
    load();
}

void TopTenScreen::setFrame() noexcept
{
    m_frame.setPosition(FRAME_OUTLINE, FRAME_OUTLINE);
    m_frame.setOutlineColor(sf::Color::Blue);
    m_frame.setOutlineThickness(FRAME_OUTLINE);
    sf::Color blush{255, 240, 245};
    m_frame.setFillColor(blush);
    m_window.setFramerateLimit(10);
}

void TopTenScreen::setTexts(float a_windowWidth, float a_windowHeight)
{
    if(!m_font.loadFromFile("../arkanoid/fonts/cabin-sketch.bold.ttf")) {
        throw std::domain_error("file error\n");
    }
	m_text.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    m_text.setPosition(a_windowWidth / 2, a_windowHeight / 4);

    sf::Color darkRed(139, 0, 0);
    m_title.setFillColor(darkRed);
    sf::FloatRect textBounds2 = m_title.getLocalBounds();
    m_title.setOrigin(textBounds2.left + textBounds2.width / 2.0f, textBounds2.top + textBounds2.height / 2.0f);
    m_title.setPosition(a_windowWidth / 2, a_windowHeight / 6);
}

void TopTenScreen::load() 
{
    std::ifstream reader(m_fileName);
    if(!reader.is_open()) {
        throw std::domain_error("Unable to open file.\n");
    }
   int score = 555;
   float time = 0.0;

    while(reader >> score) {
        reader >> time >> std::ws; 
        std::string name;
        std::getline(reader, name);
        PlayerResult results{score, time};
        m_topTenScores.emplace(results, name);
    }
    reader.close();
}

TopTenScreen::ExitStatus TopTenScreen::run()
{
	refresh();
    ExitStatus status = ExitStatus::CONTINUE;
    while (m_window.isOpen()) {
        status = flow();
        if(status == ExitStatus::EXIT 
        || status == ExitStatus::CLOSE_WINDOW) {
            return status;
        }
        m_window.display();
    }
    return status;
}

TopTenScreen::ExitStatus TopTenScreen::flow()
{
    sf::Event event;
    while(m_window.pollEvent(event)) {
        //closing the whole window
        if(event.type == sf::Event::Closed) {
            return ExitStatus::CLOSE_WINDOW;
        }
        //return to menu
        if(event.type == sf::Event::KeyPressed) {
            return ExitStatus::EXIT;
        }
    }
    m_window.clear();
    m_window.draw(m_frame);
    m_window.draw(m_text);
    m_window.draw(m_title);
    return ExitStatus::CONTINUE;
}

void TopTenScreen::fixStringToSize(std::string& a_string, size_t a_size) const noexcept
{
    sf::Text nameTempText{a_string, m_font, 30};
    sf::FloatRect textBounds = nameTempText.getLocalBounds();

    while(textBounds.width <= a_size) {
        a_string += "-";
        nameTempText.setString(a_string);
        textBounds = nameTempText.getLocalBounds();
    }
}

void TopTenScreen::refresh()
{
	//update sf::text from map
	std::string list = "NAME";
    for(size_t i = 0; i < (SPACE_SCORE_NAME / 2); ++i) {
        list += " ";
    }
    list += "POINTS";
    for(size_t i = 0; i < (SPACE_SCORE_NAME / 2); ++i) {
        list += " ";
    }
    list += "MINUTES\n";

	for(auto const& p : m_topTenScores){
        std::string name = p.second; 
        fixStringToSize(name, SPACE_IN_TABLE);
        list += name; 

        std::string points = std::to_string(p.first.m_points);
        fixStringToSize(points, SPACE_IN_TABLE);
		list += points;

        std::string time = Clock::formatElapsedTime(p.first.m_timeMilli);
        list += time;
        list += "\n";
	}

	m_text.setString(list);
}

void TopTenScreen::addPlayerToTable(std::string a_name, int const& a_score, float const& a_timeMili)
{
    assert(isPlayerInTopTen(a_score, a_timeMili));
    PlayerResult results{a_score, a_timeMili};
    m_topTenScores.emplace(results, a_name);
    save();
}

void TopTenScreen::save() const
{
    // bug to fix - m_fileName (instead of "../arkanoid/top10.dat") do domain_error
    std::ofstream writer(m_fileName);
    if (!writer.is_open()) {
        throw std::domain_error("Unable to open file.\n");
    }
    auto itr = m_topTenScores.begin();
    auto const end = m_topTenScores.end();
    while(itr != end) {
        writer << (*itr).first.m_points << ' ' << (*itr).first.m_timeMilli << ' ' << (*itr).second << '\n';
        ++itr;
    }
}

bool TopTenScreen::isPlayerInTopTen(int const& a_score, float const& a_timeMili) noexcept
{
    if(m_topTenScores.size() < 10) {
        return true;
    }   
    auto end = m_topTenScores.end();
    --end;
    // score is bigger that the smaller score in table
    if((*end).first.m_points <= a_score) {
        m_topTenScores.erase(end);
        return true;
    }
    auto itr = m_topTenScores.begin();
    ++end;
    // there is equal score - Get in if the time is less
    while(itr != end) {
        if(((*itr).first.m_points == a_score) 
        && ((*itr).first.m_timeMilli > a_timeMili)) {
            m_topTenScores.erase(itr);
            return true;
        }
        ++itr;
    }
    return false;
}

} //namespace arkanoid
