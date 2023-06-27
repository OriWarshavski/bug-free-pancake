#include <iostream>
#include <fstream>

#include "json.hpp"
#include "bricksGroup.hpp"

using json = nlohmann::json;

namespace arkanoid {

BrickGroup::BrickGroup(float a_totalWidth, float a_brickHeight
                    , float a_startX, float a_startY)
: m_totalWidth(a_totalWidth)
, m_rowHeight(a_brickHeight)
, m_startX(a_startX)
, m_startY(a_startY)
, m_bricks{}
, m_unbreackables{}
{
    createListOfBricks();
    createListOfUnbreackables();
}

bool BrickGroup::levelUp()
{
    //there are no more levels
    if(m_levelNum == MAX_LEVEL) {
        return false;
    }

    ++m_levelNum;
    createListOfBricks();
    createListOfUnbreackables();

    return true;
}

void BrickGroup::createListOfBricks()
{
    std::string fileName = "../arkanoid/levels/level-" + std::to_string(m_levelNum) + ".json";
    std::ifstream level(fileName);
    if (!level.is_open()) {
        std::cerr << "Error opening file." << std::endl;
    }

    json j;
    level >> j;

    int bricks_in_row = j["bricks in row"];
    float brickWidth = m_totalWidth / static_cast<float>(bricks_in_row);

    for (auto& object : j["objects"]) {
        std::array<int, 3> readColor = object["color"].get<std::array<int, 3>>();
        sf::Color color{};
        color.r = readColor[0];
        color.g = readColor[1];
        color.b = readColor[2];
        Brick brick{m_startX + (object["location"]["x"].get<float>() * brickWidth)
                    , m_startY + (object["location"]["y"].get<float>() * m_rowHeight)
                    , brickWidth, m_rowHeight, color, BRICK_THICKNESS};
        m_bricks.push_back(brick);
    }
}

void BrickGroup::createListOfUnbreackables()
{
    std::string fileName = "../arkanoid/levels/level-" + std::to_string(m_levelNum) + ".json";
    std::ifstream level(fileName);
    if (!level.is_open()) {
        std::cerr << "Error opening file." << std::endl;
    }

    json j;
    level >> j;

    int bricks_in_row = j["bricks in row"];
    float brickWidth = m_totalWidth / static_cast<float>(bricks_in_row);

    for (auto& object : j["unbreakables"]) {
        std::array<int, 3> readColor = object["color"].get<std::array<int, 3>>();
        sf::Color color{};
        color.r = readColor[0];
        color.g = readColor[1];
        color.b = readColor[2];
        UnbreackableBrick brick{m_startX + (object["location"]["x"].get<float>() * brickWidth)
                    , m_startY + (object["location"]["y"].get<float>() * m_rowHeight)
                    , brickWidth, m_rowHeight, color, BRICK_THICKNESS};
        m_unbreackables.push_back(brick);
    }
}

void BrickGroup::draw(sf::RenderWindow& a_window) const 
{
    //draw normal bricks
    auto itrBricks = m_bricks.begin();
    auto const endBricks = m_bricks.end();
    while(itrBricks != endBricks) {
        a_window.draw(*itrBricks);
        ++itrBricks;
    }
    //draw unbreackable bricks
    auto itrUnbreackable = m_unbreackables.begin();
    auto const endUnbreackable = m_unbreackables.end();
    while(itrUnbreackable != endUnbreackable) {
        a_window.draw(*itrUnbreackable);
        ++itrUnbreackable;
    }
}

int BrickGroup::pointsAccordingColor(sf::Color const& a_color)
{
    int result = -1;
    for(int i = 0; i < MAX_COLOR_NUMBER; ++i) {
        if(a_color == m_colorArray[i]) {
            //last color == grey --> multiply by the level number
            if(i == MAX_COLOR_NUMBER - 1) {
                result = (m_colorPoints[i] * m_levelNum);
            }
            else {
                result = m_colorPoints[i];
            }
        }
    }
    //color didnt found
    assert(result != -1);
    return result;
}

bool BrickGroup::breakBrick(const sf::Rect<float>& a_bounds, RectEadges& a_returnBrickEdges, int& a_points) noexcept 
{
    auto itr = m_bricks.begin();
    auto const& end = m_bricks.end();
    while(itr != end) {
        sf::Rect<float> brickBounds = (*itr).getGlobalBounds();
        if(brickBounds.intersects(a_bounds)) {
            a_points = pointsAccordingColor((*itr).getFillColor());
            m_bricks.erase(itr);
            RectEadges brickEdges(brickBounds.left, brickBounds.top, brickBounds.left + brickBounds.width, brickBounds.top + brickBounds.height);
            a_returnBrickEdges = brickEdges;
            return true;
        }
        ++itr;
    }
    auto itrUnbreackable = m_unbreackables.begin();
    auto const endUnbreackable = m_unbreackables.end();
    while(itrUnbreackable != endUnbreackable) {
        sf::Rect<float> brickBounds = (*itrUnbreackable).getGlobalBounds();
        if(brickBounds.intersects(a_bounds)) {
            RectEadges brickEdges(brickBounds.left, brickBounds.top, brickBounds.left + brickBounds.width, brickBounds.top + brickBounds.height);
            a_returnBrickEdges = brickEdges;
            a_points = 0;
            return true;
        }
        ++itrUnbreackable;
    }
    return false;
}

bool BrickGroup::empty() const noexcept
{
    return m_bricks.empty();
}

void BrickGroup::reset() noexcept
{
    m_levelNum = 1;
    createListOfBricks();
    createListOfUnbreackables();
}

} // namespace arkanoid
