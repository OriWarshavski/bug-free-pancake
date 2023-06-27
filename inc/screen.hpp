#pragma once

#include <SFML/Graphics.hpp>

namespace arkanoid {

class Screen {
public:
    enum class ExitStatus {PLAY, EXIT, CONTINUE, CLOSE_WINDOW};
    virtual ~Screen() = default;

protected:
    Screen() = default;
    Screen(const Screen &a_other) = default;
    Screen& operator=(const Screen &a_other) = default;

    virtual ExitStatus run() = 0;

};

} // namespace arkanoid01
