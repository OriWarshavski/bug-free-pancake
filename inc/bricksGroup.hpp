#pragma once

#include <SFML/Graphics.hpp>
#include <utility>
#include <list>
#include <tuple>

#include "brick.hpp"
#include "unbreackable_brick.hpp"

namespace arkanoid {

//3 rows of bricks
class BrickGroup {
public:
    explicit BrickGroup(float a_totalWidth, float a_brickHeight, float a_startX, float a_startY);
    BrickGroup(const BrickGroup &a_other) = default;
    BrickGroup& operator=(const BrickGroup &a_other) = default;
    ~BrickGroup() = default;

    void draw(sf::RenderWindow& a_window) const;

    using RectEadges = std::tuple<float, float, float, float>;
    //in order of: left, top, right, bottom
    bool breakBrick(const sf::Rect<float>& a_bounds, RectEadges& a_returnBrickEdges, int& a_points) noexcept;
    bool empty() const noexcept;
    void reset() noexcept;
    bool levelUp();

    void createLevelOne() const;
    void createLevelTwo() const;
    void createLevel3() const;

private:
    void createListOfBricks();
    void createListOfUnbreackables();
    int pointsAccordingColor(sf::Color const& a_color);

private:
    //consts
    static constexpr float BRICK_THICKNESS = 2; 
    static constexpr int BRICKS_IN_ROW = 11; 
    static constexpr int NUMBER_OF_ROWS = 6; 
    static constexpr int MAX_COLOR_NUMBER = 9;

    sf::Color LimeGreen{50, 210, 50};
    sf::Color Orange{255, 165, 0};
    sf::Color Salmon{250, 128, 114};
    sf::Color RoyalBlue{65, 105, 225};
    sf::Color Crimson{220, 20, 60};
    sf::Color Silver{192, 192, 192};
    sf::Color LightBlue{0, 200, 255};
    sf::Color LightPink{255, 153, 204};
    sf::Color White{255, 255, 255};
    sf::Color Gold{255, 215, 0};

    //silver must be the last color !!!
    sf::Color m_colorArray[MAX_COLOR_NUMBER] =
            {LimeGreen, Orange, Salmon
            , RoyalBlue, Crimson, LightBlue, LightPink, White ,Silver};
    /*By each brick's index in the color array, the points
    array displays the points for that brick*/
    static int constexpr m_colorPoints[MAX_COLOR_NUMBER] = 
                        {80, 120, 60, 100, 90, 70, 110, 50, 50};

    static constexpr int MAX_LEVEL = 3;
    
    //members
    float m_totalWidth;
    float m_rowHeight;
    float m_startX;
    float m_startY;

    int m_levelNum = 1;
    std::list<Brick> m_bricks;  
    std::list<UnbreackableBrick> m_unbreackables;  
};

} // namespace arkanoid
