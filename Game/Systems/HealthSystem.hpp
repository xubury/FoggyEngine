#ifndef HEALTHSYSTEM_HPP
#define HEALTHSYSTEM_HPP

#include "EntitySystem/Entities/Entity.hpp"

struct HealthComp : foggy::es::Component<HealthComp, foggy::es::DefaultEntity> {
    explicit HealthComp(int hp) : hp(hp) {}
    int hp;
};

class HealthSystem
    : public foggy::es::System<HealthComp, foggy::es::DefaultEntity> {
   public:
    virtual void update(
        foggy::es::EntityManager<foggy::es::DefaultEntity> &manager,
        const sf::Time &delta_time) override;
};

#endif /* HEALTHSYSTEM_HPP */
