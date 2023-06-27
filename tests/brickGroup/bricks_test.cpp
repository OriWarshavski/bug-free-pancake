#include <string>
#include <iostream>

#include "bricksGroup.hpp"

static constexpr float WINDOW_WIDTH = 800;
static constexpr float WINDOW_HEIGHT = 900;
static constexpr float FRAME_THICKNESS = 2;
static constexpr float BRICKS_TOTAL_WIDTH = WINDOW_WIDTH - 2 * FRAME_THICKNESS;
static constexpr float BRICK_HEIGHT = WINDOW_HEIGHT / 25;
static constexpr float BRICKS_X = FRAME_THICKNESS;
static constexpr float BRICKS_Y = FRAME_THICKNESS + WINDOW_HEIGHT / 12;

int main() {
    using namespace arkanoid01;
    sf::RenderWindow w{sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arkanoid Game"};
    BrickGroup bricks{BRICKS_TOTAL_WIDTH, BRICK_HEIGHT, BRICKS_X, BRICKS_Y};
    //bricks.createLevel3();
    sf::Event event;
    bricks.levelUp();
    //bricks.levelUp();
    while (w.isOpen()) {
        while(w.pollEvent(event)) {
            if(((event.type == sf::Event::KeyPressed) 
            && (event.key.code == sf::Keyboard::Escape))) {
                w.close();
                break;
            }
            if(event.type == sf::Event::Closed) {
                w.close();
                break;
            }
        }
        w.clear();
        bricks.draw(w);
        w.display();
    }
}

