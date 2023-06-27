#pragma once

#include <SFML/Graphics.hpp>
#include <utility>

#include "ball.hpp"
#include "paddle.hpp"
#include "bricksGroup.hpp"

namespace arkanoid {

bool isBallCollideFrame(Ball& a_ball, sf::RectangleShape const& a_frame, std::pair<float, float>& a_updateOffset, bool& a_isBallFellDown) noexcept;

bool isBallCollidePaddle(Ball& a_ball, sf::RectangleShape const& a_paddle) noexcept;

void ballPaddleCollition(Ball& a_ball, sf::RectangleShape const& a_paddle, std::pair<float, float>& a_updateOffset);

bool isPaddleCollideRightFrame(Paddle const& a_paddle, sf::RectangleShape const& a_frame) noexcept;

bool isPaddleCollideLeftFrame(Paddle const& a_paddle, sf::RectangleShape const& a_frame) noexcept;

bool isBallCollideBrick(Ball& a_ball, BrickGroup& a_bricks, std::pair<float, float>& a_updateOffset, int& a_points) noexcept;



} // namespace arkanoid
