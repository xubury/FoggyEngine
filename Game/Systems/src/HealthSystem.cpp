#include "Game/Systems/HealthSystem.hpp"

void HealthSystem::Update(
    foggy::es::EntityManager<foggy::es::DefaultEntity> &manager,
    const sf::Time &) {
    HealthComp::Handle hp;
    auto view = manager.GetByComponents(hp);
    auto end = view.End();
    for (auto cur = view.Begin(); cur != end; ++cur) {
        if (hp->hp <= 0) {
            manager.Remove(cur->ID());
        }
    }
}
