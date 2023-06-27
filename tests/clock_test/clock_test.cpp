#include <string>
#include <iostream>

#include "clock.hpp"

int main() {
    using namespace arkanoid01;
    sf::RenderWindow w{sf::VideoMode(800, 900), "Arkanoid Game"};
    Clock clock{400, 100};
    sf::Event event;
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
        clock.drawClock(w);
        w.display();
    }
    std::cout << clock.getTime() << '\n';
}