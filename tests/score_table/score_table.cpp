#include <fstream>

#include "top_ten_screen.hpp"

void openFile()
{
    std::ofstream file{"top10.dat", std::ios::in | std::ios::out | std::ios::app};
    //open top10 file if doesnt exists
    if (!file) { // check if file doesn't exist
        file.open("top10.dat", std::ios::out); // create the file
        file.close(); // close the file
    }
}

int main() {
    using namespace arkanoid01;
    openFile();
    sf::RenderWindow w{sf::VideoMode(800, 900), "Arkanoid Game"};
    TopTenScreen test{800, 900, w, "top10.dat"};
    test.addPlayerToTable("eron", 333, 12.2);
    test.addPlayerToTable("   mu mu", 224, 11.1);
    test.run();

}