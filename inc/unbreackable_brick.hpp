#pragma once

#include "brick.hpp"

namespace arkanoid {

class UnbreackableBrick : public Brick {
public:
    explicit UnbreackableBrick(float a_startX, float a_startY, float a_width, float a_height, sf::Color a_color, float a_thickness);
    UnbreackableBrick(const UnbreackableBrick &a_other) = default;
    UnbreackableBrick& operator=(const UnbreackableBrick &a_other) = default;
    ~UnbreackableBrick() = default;
};

} // namespace arkanoid01
