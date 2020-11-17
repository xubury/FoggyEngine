#include <iostream>

#include "Game.hpp"

int main() {
    foggy::Game game(1280, 1080, "foggy");
    game.Run(30);
    return 0;
}
