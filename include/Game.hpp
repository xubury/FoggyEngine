#ifndef GAME_H
#define GAME_H

#include <Box2D/Box2D.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <list>
namespace foggy {

class Game {
   public:
    Game(int width, int height, const std::string &title);
    Game(const Game &) = delete;

    Game &operator=(const Game &) = delete;

    virtual ~Game();

    void Run(int min_fps);

    float GetFps();

    static b2Body *CreateBody(b2World &world, int pox_x, int pos_y, int size_x,
                              int size_y, b2BodyType type = b2_dynamicBody);

   private:
    void Render();

    void Update(sf::Time &delta_time);

    void ProcessEvent();

    sf::RenderWindow m_window;

    sf::Time m_time_since_last_update;

    std::list<b2Body *> m_bodies;

    b2World m_world;
};

inline float Game::GetFps() {
    return 1.f / m_time_since_last_update.asSeconds();
}

} /* namespace foggy */

#endif /* GAME_H */
