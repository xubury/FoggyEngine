#ifndef GAME_H
#define GAME_H

#include <Box2D/Box2D.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <list>

#include "Player.hpp"
#include "World/World.hpp"

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

    sf::Clock m_fps_clock;

    sf::Text m_fps;

    foggy::World m_world;

    sf::View m_hud_camera;

    std::shared_ptr<Player> m_player;
};

inline float Game::GetFps() {
    return 1.f / m_fps_clock.getElapsedTime().asSeconds();
}

#endif /* GAME_H */
