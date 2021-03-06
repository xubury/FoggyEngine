#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <stdint.h>

#include <cassert>

#include "EntitySystem/Defines.hpp"

namespace foggy {
namespace es {

template <typename ENTITY>
class EntityManager;

template <typename COMPONENT, typename ENTITY>
class ComponentHandle {
   public:
    ComponentHandle(const ComponentHandle &) = default;
    ComponentHandle &operator=(const ComponentHandle &) = default;

    ComponentHandle();

    bool isValid() const;

    COMPONENT *get();
    const COMPONENT *get() const;

    COMPONENT *operator->();
    const COMPONENT *operator->() const;

   private:
    friend class EntityManager<ENTITY>;

    ComponentHandle(const EntityManager<ENTITY> *manager, uint32_t entity_id);

    const EntityManager<ENTITY> *m_manager;
    uint32_t m_entity_id;
};

template <typename ENTITY>
class VComponent {
   public:
    virtual ~VComponent() = default;
    uint32_t ownerID() const;
    EntityManager<ENTITY> *manager() { return m_manager; }

   protected:
    friend class EntityManager<ENTITY>;

    VComponent();

    static uint32_t s_family_counter;

   private:
    EntityManager<ENTITY> *m_manager;
    uint32_t m_owner_id;
};

#define ES_INIT_VCOMPONENT(ENTITY) \
    template <>                    \
    uint32_t foggy::es::VComponent<ENTITY>::s_family_counter = 0;

template <typename COMPONENT, typename ENTITY>
class Component : public VComponent<ENTITY> {
   public:
    Component(const Component &) = delete;
    Component &operator=(const Component &) = delete;

    Component() = default;
    virtual ~Component() = default;

    void remove();
    static uint32_t family();
    using Handle = ComponentHandle<COMPONENT, ENTITY>;
};

template <typename COMPONENT, typename ENTITY>
inline bool ComponentHandle<COMPONENT, ENTITY>::isValid() const {
    return m_manager != nullptr;
}

template <typename COMPONENT, typename ENTITY>
ComponentHandle<COMPONENT, ENTITY>::ComponentHandle()
    : m_manager(nullptr), m_entity_id(-1) {}

template <typename COMPONENT, typename ENTITY>
ComponentHandle<COMPONENT, ENTITY>::ComponentHandle(
    const EntityManager<ENTITY> *manager, uint32_t entity_id)
    : m_manager(manager), m_entity_id(entity_id) {}

template <typename COMPONENT, typename ENTITY>
inline COMPONENT *ComponentHandle<COMPONENT, ENTITY>::get() {
    assert(isValid());
    return m_manager->template getComponentPtr<COMPONENT>(m_entity_id);
}

template <typename COMPONENT, typename ENTITY>
inline const COMPONENT *ComponentHandle<COMPONENT, ENTITY>::get() const {
    assert(isValid());
    return m_manager->template getComponentPtr<COMPONENT>(m_entity_id);
}

template <typename COMPONENT, typename ENTITY>
inline COMPONENT *ComponentHandle<COMPONENT, ENTITY>::operator->() {
    assert(isValid());
    return m_manager->template getComponentPtr<COMPONENT>(m_entity_id);
}

template <typename COMPONENT, typename ENTITY>
inline const COMPONENT *ComponentHandle<COMPONENT, ENTITY>::operator->() const {
    assert(isValid());
    return m_manager->template getComponentPtr<COMPONENT>(m_entity_id);
}

template <typename ENTITY>
VComponent<ENTITY>::VComponent() : m_manager(nullptr), m_owner_id(-1) {}

template <typename ENTITY>
inline uint32_t VComponent<ENTITY>::ownerID() const {
    return m_owner_id;
}

template <typename COMPONENT, typename ENTITY>
inline void Component<COMPONENT, ENTITY>::remove() {
    VComponent<ENTITY>::m_manager->template removeComponent<COMPONENT>(
        VComponent<ENTITY>::m_owner_id);
}

template <typename COMPONENT, typename ENTITY>
inline uint32_t Component<COMPONENT, ENTITY>::family() {
    static uint32_t family = VComponent<ENTITY>::s_family_counter++;
    assert(family < MAX_COMPONENTS);
    return family;
}

}  // namespace es
}  // namespace foggy

#endif /* COMPONENT_HPP */
