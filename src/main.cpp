#include "Game.hpp"
#include <iostream>

int main() {
    game::Game g;
    if (!g.init()) {
        std::cerr << "Failed to initialize game." << std::endl;
        return 1;
    }
    g.run();
    return 0;
}
