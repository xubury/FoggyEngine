#ifndef SKIN_H
#define SKIN_H

#include <sol/sol.hpp>

#include "AnimationSystem/AnimatedSprite.hpp"
#include "EntitySystem/ES.hpp"
namespace foggy {
namespace component {

struct Skin : es::Component<Skin, es::DefaultEntity> {
   public:
    explicit Skin(sol::state &lua);

    std::string GetCurrentState();

    void Update();

    as::AnimatedSprite m_sprite;
    std::unordered_map<int, as::Animation *> m_animations;

   private:
    sol::state &lua;
};

}  // namespace component
}  // namespace foggy

#endif /* SKIN_H */
