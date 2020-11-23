#ifndef SKIN_H
#define SKIN_H

#include "AnimationSystem/AnimatedSprite.hpp"
#include "EntitySystem/ES.hpp"
namespace foggy {
namespace component {

struct Skin : es::Component<Skin, es::DefaultEntity> {
   public:
    explicit Skin() {}
    as::AnimatedSprite m_sprite;
    std::unordered_map<int, as::Animation *> m_animations;
};

}  // namespace component
}  // namespace foggy

#endif /* SKIN_H */
