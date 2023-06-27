#include "collision.hpp"
#include <tuple>
#include <iostream>

namespace arkanoid {

using RectangleBounds = std::tuple<float, float, float, float>;
static void offestBall(Ball& a_ball, RectangleBounds const& a_brickbounds, std::pair<float, float>& a_updateOffset);

bool isBallCollideFrame(Ball& a_ball, sf::RectangleShape const& a_frame, std::pair<float, float>& a_updateOffset, bool& isBallFellDown) noexcept
{
    bool answer = false;
    sf::Vector2f pos = a_ball.getPosition();
    const int rightBoarder = a_frame.getSize().x - a_frame.getOutlineThickness();
    const int bottomBoarder = a_frame.getSize().y - a_frame.getOutlineThickness();
    isBallFellDown = false;
    auto [offsetX, offsetY] = a_ball.velocityCopy();
    auto const& [edgeCircleX, edgeCircleY] = std::make_pair(pos.x + offsetX + a_ball.getRadius(), pos.y + offsetY + a_ball.getRadius());
    if(edgeCircleY >= bottomBoarder) {
        isBallFellDown = true;
    }
    if(edgeCircleY <= a_ball.getRadius() + a_frame.getOutlineThickness()) {
        offsetY *= -1;
        answer = true;
    }
    if(edgeCircleX >= rightBoarder || edgeCircleX <= a_ball.getRadius() + a_frame.getOutlineThickness()) {
        offsetX *= -1;
        answer = true;
    }
    a_updateOffset = std::make_pair(offsetX, offsetY);
    return answer;
}

bool isBallCollidePaddle(Ball& a_ball, sf::RectangleShape const& a_paddle) noexcept
{
    if(a_ball.getGlobalBounds().intersects(a_paddle.getGlobalBounds())) {
        return true;
    }
    return false;
}

void ballPaddleCollition(Ball& a_ball, sf::RectangleShape const& a_paddle, std::pair<float, float>& a_updateOffset) 
{
    assert(isBallCollidePaddle(a_ball, a_paddle));
    auto [offsetX, offsetY] = a_ball.velocityCopy();
    // bug: ball stuck inside paddle in one direction and gets out from another
    sf::FloatRect paddleBounds = a_paddle.getGlobalBounds();
    sf::Vector2f pos = a_ball.getPosition();
    float circleBottom = pos.x + a_ball.getRadius();
    float middlePaddle = paddleBounds.left + (paddleBounds.width / 2.0f);
    // ball touch left side of paddle - move left
    if(circleBottom < middlePaddle) {
        offsetY *= -1;
        offsetX = -abs(offsetX);
    }
    // ball touch right side of paddle - move right
    //bug - always false:
    if(middlePaddle <= circleBottom) {
        offsetY *= -1;
        offsetX = abs(offsetX);
    }
    a_updateOffset = std::make_pair(offsetX, offsetY);
}

bool isPaddleCollideRightFrame(Paddle const& a_paddle, sf::RectangleShape const& a_frame) noexcept
{
    int leftEdge = a_paddle.getGlobalBounds().left;
    int rightEdge = leftEdge + a_paddle.getGlobalBounds().width;
    int rightFramePos = a_frame.getSize().x;
    if(rightEdge >= rightFramePos) {
        return true;
    }
    return false;
}

bool isPaddleCollideLeftFrame(Paddle const& a_paddle, sf::RectangleShape const& a_frame) noexcept
{
    int leftEdge = a_paddle.getGlobalBounds().left;
    if(leftEdge - 2 * a_frame.getOutlineThickness() <= 0) {
        return true;
    }
    return false;
}

using RectangleBounds = std::tuple<float, float, float, float>;
bool isBallCollideBrick(Ball& a_ball, BrickGroup& a_bricks, std::pair<float, float>& a_updateOffset, int& a_points) noexcept
{
    RectangleBounds brickBounds;
    if(a_bricks.breakBrick(a_ball.getGlobalBounds(), brickBounds, a_points)) {
        offestBall(a_ball, brickBounds, a_updateOffset);
        return true;
    }
    return false;
}

static void offestBall(Ball& a_ball, RectangleBounds const& a_brickbounds, std::pair<float, float>& a_updateOffset)
{
    sf::Vector2f pos = a_ball.getPosition();
    auto [offsetX, offsetY] = a_ball.velocityCopy();
    auto const& [circleLeft, circleTop, circleRight, circleBottom] 
                = std::make_tuple(pos.x - offsetX - a_ball.getRadius()
                , pos.y - offsetY - a_ball.getRadius()
                , pos.x + offsetX + a_ball.getRadius()
                , pos.y + offsetY + a_ball.getRadius());
    auto const& [brickLeft, brickTop, brickRight, brickBottom] = a_brickbounds;
    //ball collided brick from bottom/top - x diraction remains, y direction * (-1)
    if(circleLeft < brickRight || brickLeft < circleRight) {
        offsetY *= -1;
    }
    //ball collided brick from side - y diraction remains, x direction * (-1)
    else {
        offsetX *= -1;
        std::cout << "side\n";
    } 
    a_updateOffset = std::make_pair(offsetX, offsetY);
}

} //namespace arkanoid
