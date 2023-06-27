#include <iostream>

#include "game_manager.hpp"

namespace arkanoid {

static void openFile()
{
    std::ofstream file{"top10.dat", std::ios::in | std::ios::out | std::ios::app};
    //open top10 file if doesnt exists
    if (!file) { // check if file doesn't exist
        file.open("top10.dat", std::ios::out); // create the file
        file.close(); // close the file
    }
}

GameManager::GameManager()
: m_frame(windowFrame())
, m_window{sf::VideoMode(800, 900), "Arkanoid Game"}
, m_ball{BALL_X, BALL_Y, BALL_RADIUS, BALL_OUTLINE}
, m_paddle{PADDLE_X, PADDLE_Y, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_OUTLINE}
, m_bricks{BRICKS_TOTAL_WIDTH, BRICK_HEIGHT , BRICKS_X, BRICKS_Y}
, m_player{SCORE_X, SCORE_Y, LIVES_X, LIVES_Y, CLOCK_X, CLOCK_Y}
, m_menuScrean{WINDOW_WIDTH, WINDOW_HEIGHT, m_frame, m_window}
, m_topTenFile{"top10.dat", std::ios::in | std::ios::out | std::ios::app}
, m_topTenScreen{WINDOW_WIDTH, WINDOW_HEIGHT, m_window, "../arkanoid/top10.dat"}
, m_input{m_window}
, m_clock{}
, m_level{1}
, m_music{}
, m_sounds{}
{
    openFile();
    m_window.setFramerateLimit(FRAMERATE_LIMIT);
    setMusic();
}

void GameManager::setMusic()
{
    std::string fileName = "../arkanoid/audio/level-";
    fileName += std::to_string(m_level);
    fileName += ".wav";
    if (!m_music.openFromFile(fileName)) {
        throw std::domain_error("file opening error\n");
    }
    m_music.setVolume(20);
    m_music.setLoop(true);         // make it loop
}


sf::RectangleShape GameManager::windowFrame()
{
    sf::RectangleShape frame(sf::Vector2f(WINDOW_WIDTH - FRAME_THICKNESS * 2, WINDOW_HEIGHT - FRAME_THICKNESS * 2));
    frame.setPosition(FRAME_THICKNESS, FRAME_THICKNESS);
    frame.setOutlineColor(sf::Color::Blue);
    sf::Color blush{255, 240, 245};
    frame.setFillColor(blush);
    frame.setOutlineThickness(FRAME_THICKNESS);
    return frame;
}

GameManager::ExitStatus GameManager::run()
{
    bool firstStart = true;
    MenuScreen::ExitStatus menuStatus = MenuScreen::ExitStatus::CONTINUE;
    GameManager::FinishStatus GameStatus = GameManager::FinishStatus::PAUSE;
    while(menuStatus != MenuScreen::ExitStatus::EXIT) {
        //run manu if game paused / loss / at the beginning / game finished
        if(GameStatus != GameManager::FinishStatus::LEVEL_FINISHED) {
            if(GameStatus == FinishStatus::CLOSE_WINDOW) {
                break;
            }
            menuStatus = m_menuScrean.run();
        //run game if the PLAY button was pressed
            if(menuStatus == MenuScreen::ExitStatus::PLAY) {
                if(firstStart) {
                    firstStart = false;
                    m_player.startTimeCount();
                }
                m_music.play();
                GameStatus = runGame(); 
                m_music.pause();  
            }
        }
        
        //GameStatus == LEVEL_FINISHED: continue to next level
        else {
            setMusic();
            if(!m_sounds.isMute()) {
                m_music.play();
            }
            GameStatus = runGame(); 
            m_music.pause(); 
        }
        
    }
    
    m_window.close(); 
    return ExitStatus::EXIT;
}

GameManager::FinishStatus GameManager::runGame()
{
    while (m_window.isOpen()) {
        if(m_player.lives() <= 0 || m_bricks.empty()) {
            return gameOver();
        }
        GameManager::ExitStatus status = gameFlow();
        // play/exit/close window
        if(status != ExitStatus::CONTINUE) {
            if(status == ExitStatus::CLOSE_WINDOW) {
                return FinishStatus::CLOSE_WINDOW; 
            }
            //play option
            return GameManager::FinishStatus::PAUSE;
        }
        drawingGame();
        if(m_isBallMoving) {
            ballMoves(m_frame);
        }
        m_window.display();
    }
    return GameManager::FinishStatus::PAUSE;
}

GameManager::FinishStatus GameManager::gameOver() 
{
    GameManager::FinishStatus gameStatus = GameManager::FinishStatus::PAUSE;
    //lives are over or winning the game - run top 10
    if(m_player.lives() <= 0 || !m_bricks.levelUp()) {
        m_music.stop();
        if(m_player.lives() <= 0) {
            m_sounds.play(SoundEffects::Types::LOSS);
            
        }
        //winner - finish all levels
        else {
            m_sounds.play(SoundEffects::Types::WIN);
        }
        if(runTop10() == ExitStatus::CLOSE_WINDOW) {
            return FinishStatus::CLOSE_WINDOW;
        }
        m_player.reset();
        m_bricks.reset();
        gameStatus = GameManager::FinishStatus::LOSS;
    }
    //bricks are finished not in last level - continue to next level
    else { 
        ++m_level;
        gameStatus = GameManager::FinishStatus::LEVEL_FINISHED;
    }
    m_ball.resetPosition();
    m_paddle.resetPosition();
    return gameStatus;
}


GameManager::ExitStatus GameManager::gameFlow()
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed) {
            return ExitStatus::CLOSE_WINDOW;
        }
        if(((event.type == sf::Event::KeyPressed) 
            && (event.key.code == sf::Keyboard::Escape))) {
            return ExitStatus::EXIT;
        }
        if(event.key.code == sf::Keyboard::Right) {
            if(!(isPaddleCollideRightFrame(m_paddle, m_frame))) {
                m_paddle.moveRight();
                if(!m_isBallMoving) {
                    m_ball.moveRight(m_paddle.velocityCopy());
                }
            }
        }
        if(event.key.code == sf::Keyboard::Left) {
            if(!(isPaddleCollideLeftFrame(m_paddle, m_frame))) {
                m_paddle.moveLeft();
                if(!m_isBallMoving) {
                    m_ball.moveLeft(m_paddle.velocityCopy());
                }
            }
        }
        if((event.type == sf::Event::KeyPressed) 
            && (event.key.code == sf::Keyboard::Space)) {
            m_isBallMoving = true;
        }
        if(event.type == sf::Event::KeyPressed 
            && (event.key.code == sf::Keyboard::Q)) {
                if(m_sounds.isMute()) {
                    m_player.unmute();
                    m_sounds.unmute();
                    m_music.play();
                }
                else {
                    m_player.mute();
                    m_sounds.mute();
                    m_music.pause();
                }
            }

    }
    return ExitStatus::CONTINUE;
}

TopTenScreen::ExitStatus GameManager::runTop10()
{
    float endTimeMili = m_player.time();
    int points = m_player.score();
    if(m_topTenScreen.isPlayerInTopTen(points, endTimeMili)) {
        m_sounds.play(SoundEffects::Types::IN_TOP_10);
        std::string name;
        name = m_input.typeYourName();
        m_topTenScreen.addPlayerToTable(name, points, endTimeMili);
    }
    return m_topTenScreen.run();
}

void GameManager::drawingGame()
{
    m_window.clear();
    m_window.draw(m_frame);
    m_window.draw(m_ball);
    m_window.draw(m_paddle);
    m_bricks.draw(m_window);
    m_player.draw(m_window);
}

void GameManager::ballMoves(sf::RectangleShape const& a_frame)
{
    std::pair<float, float> offset;
    bool isBallFellDown = false;
    if(isBallCollidePaddle(m_ball, m_paddle)) {
        m_sounds.play(SoundEffects::Types::BALL_SOLID);
        ballPaddleCollition(m_ball, m_paddle, offset);
        auto [offSetX, offSetY] = offset;
        m_ball.move(offSetX, offSetY);
    }
    if(isBallCollideFrame(m_ball, a_frame, offset, isBallFellDown)) {
        m_sounds.play(SoundEffects::Types::BALL_SOLID);
        auto [offSetX, offSetY] = offset;
        m_ball.move(offSetX, offSetY);
    }
    if(isBallFellDown) {
        m_sounds.play(SoundEffects::Types::FELL);
        m_isBallMoving = false;
        m_player.liveReduce();
        m_ball.resetPosition();
        m_paddle.resetPosition();
    }
    int points = 0;
    if(isBallCollideBrick(m_ball, m_bricks, offset, points)) {
        m_sounds.play(SoundEffects::Types::BREAK);
        auto [offSetX, offSetY] = offset;
        m_ball.move(offSetX, offSetY);
        m_player.addPoints(points);
    }
    if(m_bricks.empty()) {
        m_isBallMoving = false;
    }
    else if(m_isBallMoving) {
        m_ball.move();
    }
}

} // namespace arkanoid
