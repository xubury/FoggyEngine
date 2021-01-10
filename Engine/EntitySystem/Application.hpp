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

    void update(const sf::Time &deltaTime);

    SystemManager<ENTITY> systems;
    EntityManager<ENTITY> entities;
};

template <typename ENTITY>
Application<ENTITY>::Application() : systems(entities) {
    entities.setSystems(&systems);
}

template <typename ENTITY>
void Application<ENTITY>::update(const sf::Time &deltaTime) {
    systems.updateAll(deltaTime);
    entities.update();
}

}  // namespace es
}  // namespace foggy

#endif /* APPLICATION_H */
