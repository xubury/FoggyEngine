#ifndef SKIN_HPP
#define SKIN_HPP

#include <sol/sol.hpp>

#include "AnimationSystem/AnimatedSprite.hpp"
#include "EntitySystem/ES.hpp"
namespace foggy {
namespace component {

struct Skin : es::Component<Skin, es::DefaultEntity> {
   public:
    Skin();

    void update();

    void registerLuaScript();

    as::AnimatedSprite m_sprite;
    std::unordered_map<int, as::Animation *> m_animations;
};

}  // namespace component
}  // namespace foggy

#endif /* SKIN_HPP */
