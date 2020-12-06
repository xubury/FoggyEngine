#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/System/Time.hpp>

#include "EntitySystem/Entities/EntityManager.hpp"
#include "EntitySystem/Systems/System.hpp"

namespace foggy {
namespace es {

template <typename ENTITY>
class Application {
   public:
    Application();
    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;

    void Update(const sf::Time &deltaTime);

    SystemManager<ENTITY> systems;
    EntityManager<ENTITY> entities;
};

template <typename ENTITY>
Application<ENTITY>::Application() : systems(entities) {
    entities.SetSystems(&systems);
}

template <typename ENTITY>
void Application<ENTITY>::Update(const sf::Time &deltaTime) {
    systems.UpdateAll(deltaTime);
    entities.Update();
}

}  // namespace es
}  // namespace foggy

#endif /* APPLICATION_H */
