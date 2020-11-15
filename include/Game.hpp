#ifndef GAME_H
#define GAME_H

#include <Box2D/Box2D.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <list>

#include "GameWorld.hpp"
namespace foggy {

class Game {
   public:
    Game(int width, int height, const std::string &title);
    Game(const Game &) = delete;

    Game &operator=(const Game &) = delete;

    virtual ~Game();

    void Run(int min_fps);

    float GetFps();

   private:
    void Render();

    void Update(sf::Time &delta_time);

    void ProcessEvent();

    sf::RenderWindow m_window;

    sf::Time m_time_since_last_update;

    GameWorld m_world;
};

inline float Game::GetFps() {
    return 1.f / m_time_since_last_update.asSeconds();
}

} /* namespace foggy */

#endif /* GAME_H */
