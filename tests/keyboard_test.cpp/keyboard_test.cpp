#include <string>
#include <iostream>

#include "input.hpp"

int main() {
    using namespace arkanoid01;
    sf::RenderWindow w{sf::VideoMode(800, 900), "Arkanoid Game"};
    Input test{w};
    std::string name = test.typeYourName();
    std::cout << name << '\n';

}