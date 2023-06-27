#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <utility>
#include <fstream>

#include "ball.hpp"
#include "paddle.hpp"
#include "collision.hpp"
#include "bricksGroup.hpp"
#include "score.hpp"
#include "live.hpp"
#include "player.hpp"
#include "menu_screen.hpp"
#include "top_ten_screen.hpp"
#include "input.hpp"
#include "sound_effect.hpp"

namespace arkanoid {
    
class GameManager : public Screen {
public:

    GameManager();
    GameManager(const GameManager &a_other) = delete;
    GameManager& operator=(const GameManager &a_other) = delete;
    ~GameManager() = default;

    ExitStatus run() override;

private:
    enum class FinishStatus {LEVEL_FINISHED, GAME_FINISHED, PAUSE, LOSS, CLOSE_WINDOW};

    sf::RectangleShape windowFrame();
    ExitStatus gameFlow();
    void drawingGame();
    
    FinishStatus runGame();
    void ballMoves(sf::RectangleShape const& a_frame);
    TopTenScreen::ExitStatus runTop10();
    GameManager::FinishStatus gameOver();
    void setMusic();

    
    //frame details
    static constexpr float WINDOW_WIDTH = 800;
    static constexpr float WINDOW_HEIGHT = 900;
    static constexpr float FRAME_THICKNESS = 5;
    static constexpr float FRAMERATE_LIMIT = 50;
    //paddle details
    static constexpr float PADDLE_X = (WINDOW_WIDTH / 2) - (WINDOW_WIDTH / 16);
    static constexpr float PADDLE_Y = WINDOW_HEIGHT - (WINDOW_HEIGHT / 18);
    static constexpr float PADDLE_WIDTH = WINDOW_WIDTH / 8;
    static constexpr float PADDLE_HEIGHT = WINDOW_HEIGHT / 70;
    static constexpr float PADDLE_OUTLINE = 2;
    //ball details
    static constexpr float BALL_X = WINDOW_WIDTH / 2 - (WINDOW_WIDTH / 70);
    static constexpr float BALL_Y = PADDLE_Y - 5 - 2 * (WINDOW_HEIGHT / 70);
    static constexpr float BALL_RADIUS = WINDOW_HEIGHT / 70;
    static constexpr float BALL_OUTLINE = 2;
    //bricks details
    static constexpr float BRICKS_TOTAL_WIDTH = WINDOW_WIDTH - 2 * FRAME_THICKNESS;
    static constexpr float BRICK_HEIGHT = WINDOW_HEIGHT / 25;
    static constexpr float BRICKS_X = FRAME_THICKNESS;
    static constexpr float BRICKS_Y = FRAME_THICKNESS + WINDOW_HEIGHT / 12;
    //player details
    static constexpr float SCORE_X = FRAME_THICKNESS + WINDOW_WIDTH / 40;
    static constexpr float SCORE_Y = FRAME_THICKNESS + WINDOW_HEIGHT / 40;
    static constexpr float LIVES_X =  WINDOW_WIDTH - (WINDOW_WIDTH / 6);
    static constexpr float LIVES_Y = SCORE_Y;
    static constexpr float CLOCK_X = WINDOW_WIDTH / 2 - 10;
    static constexpr float CLOCK_Y = SCORE_Y + 15;

private:
    sf::RectangleShape m_frame;
    sf::RenderWindow m_window;
    Ball m_ball;
    Paddle m_paddle;
    BrickGroup m_bricks;    
    bool m_isBallMoving = false;
    Player m_player;
    MenuScreen m_menuScrean;
    std::fstream m_topTenFile;
    TopTenScreen m_topTenScreen;
    Input m_input;
    sf::Clock m_clock;
    int m_level;
    sf::Music m_music;
    SoundEffects m_sounds;
};

} // namespace arkanoid
