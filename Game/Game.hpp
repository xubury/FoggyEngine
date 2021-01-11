#ifndef GAME_H
#define GAME_H

#include <box2d/box2d.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <list>

#include "Camera/Camera.hpp"
#include "EntitySystem/Application.hpp"
#include "GUI/Frame.hpp"
#include "Systems/HealthSystem.hpp"
#include "TileMap/Layer.hpp"
#include "TileMap/MapViewer.hpp"
#include "TileMap/VMap.hpp"
#include "TimerSystem/TimerSystem.hpp"

class Game {
   public:
    Game(int width, int height, const std::string &title);
    Game(const Game &) = delete;

    Game &operator=(const Game &) = delete;

    virtual ~Game();

    void run(int min_fps);

    float getFps();

    enum Status { MainMenu, Normal };

   private:
    void initGui();

    void initWorld();

    void render();

    void update(sf::Time &delta_time);

    void processEvent();

    void processEvents();

    void processMouseEvents();

    sf::RenderWindow m_window;

    sf::Time m_time_since_last_update;

    sf::Clock m_fps_clock;

    sf::Text m_fps;

    foggy::es::Application<foggy::es::DefaultEntity> m_app;

    int32_t m_player_id;

    foggy::ts::TimerSystem m_timer;

    foggy::Frame m_main_menu;

    foggy::Layer<foggy::es::DefaultEntity *> *m_layer;

    foggy::VMap *m_map;

    foggy::MapViewer m_viewer;

    Status m_status;
};

inline float Game::getFps() {
    return 1.f / m_fps_clock.getElapsedTime().asSeconds();
}

#endif /* GAME_H */
