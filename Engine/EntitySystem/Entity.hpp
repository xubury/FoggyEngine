#ifndef ENTITY_H
#define ENTITY_H

#include <tuple>

#include "EntitySystem/Component.hpp"
#include "EntitySystem/System.hpp"
namespace foggy {
namespace es {

template <typename ENTITY>
class EntityManager;
template <typename COMPONENT, typename ENTITY>
class Component;
template <typename COMPONENT, typename ENTITY>
class ComponentHandle;

template <typename ENTITY>
class Entity {
   public:
    Entity(Entity &&) = default;
    Entity &operator=(Entity &&) = default;

    Entity(EntityManager<ENTITY> *manager, uint32_t id);

    uint32_t ID() const;

    EntityManager<ENTITY> &GetManager();

    bool operator==(const Entity &other) const;
    bool operator!=(const Entity &other) const;

    void Remove();

    template <typename COMPONENT, typename... ARGS>
    void Add(ARGS &&...args);

    template <typename COMPONENT>
    void Remove();

    template <typename COMPONENT>
    bool Has() const;

    template <typename COMPONENT>
    ComponentHandle<COMPONENT, ENTITY> Component() const;

    template <typename... COMPONENT>
    std::tuple<ComponentHandle<COMPONENT, ENTITY>...> Components() const;

   private:
    uint32_t m_id;
    EntityManager<ENTITY> *m_manager;
};
#define ES_INIT_ENTITY(ENTITY) \
    ES_INIT_VCOMPONENT(ENTITY) \
    ES_INIT_VSYSTEM(ENTITY)

class DefaultEntity : public Entity<DefaultEntity> {
   public:
    using Entity<DefaultEntity>::Entity;
};

template <typename ENTITY>
Entity<ENTITY>::Entity(EntityManager<ENTITY> *manager, uint32_t id)
    : m_id(id), m_manager(manager) {}

template <typename ENTITY>
inline uint32_t Entity<ENTITY>::ID() const {
    return m_id;
}

template <typename ENTITY>
inline EntityManager<ENTITY> &Entity<ENTITY>::GetManager() {
    return *m_manager;
}

template <typename ENTITY>
bool Entity<ENTITY>::operator==(const Entity<ENTITY> &other) const {
    return m_id == other.m_id && m_manager == other.m_manager;
}

template <typename ENTITY>
bool Entity<ENTITY>::operator!=(const Entity<ENTITY> &other) const {
    return m_id != other.m_id || m_manager != other.m_manager;
}

template <typename ENTITY>
inline void Entity<ENTITY>::Remove() {
    m_manager->Remove(m_id);
}

template <typename ENTITY>
template <typename COMPONENT, typename... Args>
inline void Entity<ENTITY>::Add(Args &&...args) {
    m_manager->template AddComponent<COMPONENT>(m_id,
                                                std::forward<Args>(args)...);
}

template <typename ENTITY>
template <typename COMPONENT>
inline void Entity<ENTITY>::Remove() {
    m_manager->template RemoveComponent<COMPONENT>(m_id);
}

template <typename ENTITY>
template <typename COMPONENT>
inline bool Entity<ENTITY>::Has() const {
    return m_manager->template HasComponent<COMPONENT>(m_id);
}

template <typename ENTITY>
template <typename COMPONENT>
inline ComponentHandle<COMPONENT, ENTITY> Entity<ENTITY>::Component() const {
    return m_manager->template GetComponent<COMPONENT>(m_id);
}

template <typename ENTITY>
template <typename... COMPONENT>
inline std::tuple<ComponentHandle<COMPONENT, ENTITY>...>
Entity<ENTITY>::Components() const {
    return m_manager->template GetComponents<COMPONENT...>(m_id);
}

}  // namespace es
}  // namespace foggy

#endif /* ENTITY_H */
