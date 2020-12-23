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
#include "TimerSystem/TimerSystem.hpp"

class Game {
   public:
    Game(int width, int height, const std::string &title);
    Game(const Game &) = delete;

    Game &operator=(const Game &) = delete;

    virtual ~Game();

    void Run(int min_fps);

    float GetFps();

    enum Status { MainMenu, Normal };

   private:
    void InitGui();

    void InitWorld();

    void Render();

    void Update(sf::Time &delta_time);

    void ProcessEvent();

    sf::RenderWindow m_window;

    sf::Time m_time_since_last_update;

    sf::Clock m_fps_clock;

    sf::Text m_fps;

    sf::View m_hud_camera;

    foggy::Camera m_cam;

    foggy::es::Application<foggy::es::DefaultEntity> m_app;

    int32_t m_player_id;

    foggy::ts::TimerSystem m_timer;

    foggy::Frame m_main_menu;

    Status m_status;
};

inline float Game::GetFps() {
    return 1.f / m_fps_clock.getElapsedTime().asSeconds();
}

#endif /* GAME_H */
