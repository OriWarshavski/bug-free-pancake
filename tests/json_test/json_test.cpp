#include <iostream>
#include <fstream>

#include "json.hpp"
#include "bricksGroup.hpp"

using json = nlohmann::json;

static constexpr float WINDOW_WIDTH = 800;
static constexpr float WINDOW_HEIGHT = 900;
static constexpr float FRAME_THICKNESS = 5;
static constexpr float BRICKS_TOTAL_WIDTH = WINDOW_WIDTH - 2 * FRAME_THICKNESS;
static constexpr float BRICK_HEIGHT = WINDOW_HEIGHT / 25;
static constexpr float BRICKS_X = FRAME_THICKNESS;
static constexpr float BRICKS_Y = FRAME_THICKNESS + WINDOW_HEIGHT / 12;

int main() {
    using namespace arkanoid01;
    BrickGroup bricks{BRICKS_TOTAL_WIDTH, BRICK_HEIGHT, BRICKS_X, BRICKS_Y};
    bricks.createLevelOne(BRICKS_TOTAL_WIDTH, BRICK_HEIGHT, BRICKS_X, BRICKS_Y);
}



