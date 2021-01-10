#include "Configuration/Configuration.hpp"
#include "Game.hpp"
#include "TileMap/VMap.hpp"

int main() {
    Game game(1280, 720, "foggy");
    game.run(120);
    return 0;
}
