#ifndef ES_HPP
#define ES_HPP

#include "EntitySystem/Components/Component.hpp"
#include "EntitySystem/Entities/Entity.hpp"
#include "EntitySystem/Entities/EntityManager.hpp"
#include "EntitySystem/Systems/System.hpp"

namespace foggy {
namespace es {
class CollisionSystem;
class SkinSystem;
}  // namespace es

namespace component {
struct Skin;
struct Collision;
struct Controller;
struct Transform;
struct LuaScript;
}  // namespace component
}  // namespace foggy

#endif /* ES_HPP */
