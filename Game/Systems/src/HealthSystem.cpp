#include "Systems/HealthSystem.hpp"

void HealthSystem::update(
    foggy::es::EntityManager<foggy::es::DefaultEntity> &manager,
    const sf::Time &) {
    HealthComp::Handle hp;
    auto view = manager.getByComponents(hp);
    auto end = view.end();
    for (auto cur = view.begin(); cur != end; ++cur) {
        if (hp->hp <= 0) {
            manager.remove(cur->id());
        }
    }
}
