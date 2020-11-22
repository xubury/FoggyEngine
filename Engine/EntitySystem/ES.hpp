#ifndef ES_H
#define ES_H

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
}  // namespace component
}  // namespace foggy

#endif /* ES_H */
