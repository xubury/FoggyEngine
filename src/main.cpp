#include <iostream>

#include "Game.hpp"

int main() {
    foggy::Game game(640, 480, "foggy");
    game.Run(30);
    return 0;
}
