#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <algorithm>
#include <bitset>
#include <list>
#include <tuple>
#include <vector>

#include "EntitySystem/Components/Component.hpp"
#include "EntitySystem/Defines.hpp"
#include "util/Memory.hpp"

namespace foggy {
namespace es {

template <typename COMPONENT, typename ENTITY>
class ComponentHandle;

template <typename COMPONENT, typename ENTITY>
class Component;

template <class ENTITY>
class EntityManager {
   private:
    template <typename...>
    class View;

    template <typename, typename>
    friend class ComponentHandle;

   public:
    using Container = std::list<uint32_t>;

   public:
    EntityManager(const EntityManager &) = delete;
    EntityManager &operator=(const EntityManager &) = delete;

    EntityManager() = default;
    ~EntityManager();

    template <typename... ARGS>
    uint32_t Create(ARGS &&...args);

    template <typename... ARGS>
    void Emplace(uint32_t index, ARGS &&...args);

    void Remove(std::size_t id);

    void Update();

    void Reset();

    std::size_t Size();

    bool IsValid(uint32_t id) const;

    const ENTITY &Get(std::size_t id) const;
    ENTITY &Get(std::size_t id);

    const ENTITY *GetPtr(std::size_t id) const;
    ENTITY *GetPtr(std::size_t id);

    Container::const_iterator Begin() const;
    Container::const_iterator End() const;

    template <typename COMPONENT, typename... ARGS>
    void AddComponent(uint32_t id, ARGS &&...args);

    template <typename COMPONENT>
    void RemoveComponent(uint32_t id);

    template <typename COMPONENT>
    bool HasComponent(uint32_t id) const;

    template <typename COMPONENT>
    ComponentHandle<COMPONENT, ENTITY> GetComponent(uint32_t id) const;

    template <typename... COMPONENT>
    std::tuple<ComponentHandle<COMPONENT, ENTITY>...> GetComponents(
        uint32_t id) const;

    template <typename... COMPONENT>
    View<COMPONENT...> GetByComponents(
        ComponentHandle<COMPONENT, ENTITY> &...components);

   private:
    // Stores every entity that have been allocated
    std::vector<ENTITY *> m_entites_allocated;
    // Stores what components does a entity of index havs
    std::vector<std::bitset<MAX_COMPONENTS>> m_entites_component_masks;
    // Stores entities that has component of index
    std::vector<utils::memory::VPool *> m_components_entites;

    Container m_entities_index;
    Container m_entities_index_free;
    Container m_entities_to_destroy;

    void Reset(uint32_t id);

    template <typename COMPONENT>
    void CheckComponent();

    template <typename COMPONENT>
    COMPONENT *GetComponentPtr(uint32_t id) const;

    template <typename... COMPONENT>
    class View {
        class Iterator;

       public:
        View(EntityManager<ENTITY> &manager,
             const std::bitset<MAX_COMPONENTS> &mask,
             ComponentHandle<COMPONENT, ENTITY> &...components);
        Iterator Begin();
        Iterator End();

       private:
        template <int N, typename C>
        void UnpackID(std::uint32_t id);

        template <int N, typename C0, typename C1, typename... Cx>
        void UnpackID(std::uint32_t id);

        template <int N, typename C>
        void UnpackManager();

        template <int N, typename C0, typename C1, typename... Cx>
        void UnpackManager();

        EntityManager<ENTITY> &m_manager;
        const std::bitset<MAX_COMPONENTS> m_mask;
        std::tuple<ComponentHandle<COMPONENT, ENTITY> &...> m_handles;

       private:
        class Iterator {
           public:
            Iterator(View &view, EntityManager<ENTITY>::Container::iterator it,
                     EntityManager<ENTITY>::Container::iterator it_end);
            Iterator &operator++();
            ENTITY *operator*() const;
            ENTITY *operator->() const;

            bool operator==(const Iterator &other) const;
            bool operator!=(const Iterator &other) const;

           private:
            View &m_view;
            EntityManager<ENTITY>::Container::iterator m_iter;
            EntityManager<ENTITY>::Container::iterator m_iter_end;
        };
    };
};

template <class ENTITY>
EntityManager<ENTITY>::~EntityManager() {
    Reset();
}

template <class ENTITY>
template <typename... ARGS>
inline uint32_t EntityManager<ENTITY>::Create(ARGS &&...args) {
    uint32_t index = 0;
    if (!m_entities_index_free.empty()) {
        index = m_entities_index_free.front();
        m_entities_index_free.pop_front();
        m_entites_allocated[index] =
            new ENTITY(this, index, std::forward<ARGS>(args)...);
    } else {
        m_entites_component_masks.emplace_back();

        index = m_entites_allocated.size();
        m_entites_allocated.emplace_back(nullptr);

        std::size_t comp_size = m_components_entites.size();
        for (std::size_t i = 0; i < comp_size; ++i) {
            if (m_components_entites[i] != nullptr) {
                m_components_entites[i]->Resize(index + 1);
            }
        }
        m_entites_allocated[index] =
            new ENTITY(this, index, std::forward<ARGS>(args)...);
    }
    m_entities_index.emplace_back(index);
    return index;
}

template <class ENTITY>
template <typename... ARGS>
inline void EntityManager<ENTITY>::Emplace(uint32_t index, ARGS &&...args) {
    std::size_t size = m_entites_allocated.size();
    if (size <= index) {
        m_entites_allocated.resize(index + 1, nullptr);
        m_entites_component_masks.resize(index + 1, 0);
        m_entities_index.emplace_back(index);

        for (std::size_t i = size; i < index; ++i) {
            m_entities_index_free.emplace_back(i);
        }

        std::size_t comp_size = m_components_entites.size();
        for (std::size_t i = 0; i < comp_size; ++i) {
            if (m_components_entites[i] != nullptr) {
                /* resize the components pool in case the new entity needs to
                 * add a certain kind of component */
                m_components_entites[i]->Resize(index + 1);
            }
        }
    } else if (m_entites_allocated[index] !=
               nullptr) {  // already in use, free it
        Reset(index);
    } else {
        m_entities_index_free.remove(index);
        m_entities_index.emplace_back(index);
    }

    m_entites_allocated[index] =
        new ENTITY(this, index, std::forward<ARGS>(args)...);
}

template <class ENTITY>
inline void EntityManager<ENTITY>::Remove(std::size_t id) {
    m_entities_to_destroy.emplace_back(id);
}

template <class ENTITY>
inline void EntityManager<ENTITY>::Update() {
    if (!m_entities_to_destroy.empty()) {
        Container::iterator iter = m_entities_to_destroy.begin();
        Container::iterator end = m_entities_to_destroy.end();
        for (; iter != end; ++iter) {
            uint32_t id = *iter;
            ENTITY *entity = m_entites_allocated.at(id);
            if (entity != nullptr) {
                Reset(id);
                m_entities_index.erase(std::find(m_entities_index.begin(),
                                                 m_entities_index.end(), id));
            }
        }
        m_entities_to_destroy.clear();
    }
}

template <class ENTITY>
inline void EntityManager<ENTITY>::Reset() {
    m_entities_index_free.clear();
    m_entities_index.clear();

    std::size_t comp_size = m_components_entites.size();
    for (std::size_t i = 0; i < comp_size; ++i) {
        if (m_components_entites[i] != nullptr) {
            for (std::size_t j = 0; j < m_entities_index.size(); ++j) {
                m_components_entites[i]->Erase<VComponent<ENTITY>>(j);
            }
            delete m_components_entites[i];
        }
    }
    m_components_entites.clear();
    m_entites_component_masks.clear();
    std::size_t size = m_entites_allocated.size();
    for (std::size_t i = 0; i < size; ++i) {
        delete m_entites_allocated[i];
    }
    m_entites_allocated.clear();
}

template <class ENTITY>
inline std::size_t EntityManager<ENTITY>::Size() {
    return m_entites_allocated.size() - m_entities_index_free.size();
}

template <class ENTITY>
inline bool EntityManager<ENTITY>::IsValid(uint32_t id) const {
    return id < m_entites_allocated.size() &&
           m_entites_allocated[id] != nullptr;
}
template <class ENTITY>
inline const ENTITY &EntityManager<ENTITY>::Get(std::size_t id) const {
    return *m_entites_allocated.at(id);
}

template <class ENTITY>
inline ENTITY &EntityManager<ENTITY>::Get(std::size_t id) {
    return *m_entites_allocated.at(id);
}

template <class ENTITY>
inline const ENTITY *EntityManager<ENTITY>::GetPtr(std::size_t id) const {
    return m_entites_allocated.at(id);
}

template <class ENTITY>
inline ENTITY *EntityManager<ENTITY>::GetPtr(std::size_t id) {
    return m_entites_allocated.at(id);
}

template <class ENTITY>
inline EntityManager<ENTITY>::Container::const_iterator
EntityManager<ENTITY>::Begin() const {
    return m_entities_index.cbegin();
}

template <class ENTITY>
inline EntityManager<ENTITY>::Container::const_iterator
EntityManager<ENTITY>::End() const {
    return m_entities_index.cend();
}

template <class ENTITY>
template <typename COMPONENT, typename... ARGS>
inline void EntityManager<ENTITY>::AddComponent(uint32_t id, ARGS &&...args) {
    CheckComponent<COMPONENT>();
    Family family = COMPONENT::Family();

    assert(!m_entites_component_masks.at(id).test(family));
    utils::memory::Pool<COMPONENT> *pool =
        static_cast<utils::memory::Pool<COMPONENT> *>(
            m_components_entites[family]);

    pool->Emplace(id, std::forward<ARGS>(args)...);
    pool->At(id).m_owner_id = id;
    pool->At(id).m_manager = this;

    m_entites_component_masks.at(id).set(family);
}

template <class ENTITY>
template <typename COMPONENT>
inline void EntityManager<ENTITY>::RemoveComponent(uint32_t id) {
    // CheckComponent<COMPONENT>();
    Family family = COMPONENT::Family();
    assert(m_entites_component_masks.at(id).test(family));

    utils::memory::Pool<COMPONENT> *pool =
        static_cast<utils::memory::Pool<COMPONENT> *>(
            m_components_entites[family]);
    pool->Erase(id);

    m_entites_component_masks.at(id).reset(family);
}

template <class ENTITY>
template <typename COMPONENT>
inline bool EntityManager<ENTITY>::HasComponent(uint32_t id) const {
    Family family = COMPONENT::Family();
    return m_entites_component_masks.at(id).test(family);
}

template <class ENTITY>
template <typename COMPONENT>
inline ComponentHandle<COMPONENT, ENTITY> EntityManager<ENTITY>::GetComponent(
    uint32_t id) const {
    if (HasComponent<COMPONENT>(id)) {
        return ComponentHandle<COMPONENT, ENTITY>(this, id);
    }
    return ComponentHandle<COMPONENT, ENTITY>();
}

template <class ENTITY>
template <typename... COMPONENT>
inline std::tuple<ComponentHandle<COMPONENT, ENTITY>...>
EntityManager<ENTITY>::GetComponents(uint32_t id) const {
    return std::make_tuple(GetComponent<COMPONENT>(id)...);
}

template <class ENTITY>
template <typename COMPONENT>
inline COMPONENT *EntityManager<ENTITY>::GetComponentPtr(uint32_t id) const {
    Family family = COMPONENT::Family();
    return &static_cast<utils::memory::Pool<COMPONENT> *>(
                m_components_entites[family])
                ->At(id);
}

template <typename COMPONENT>
inline void GetMask(std::bitset<MAX_COMPONENTS> &mask) {
    mask.set(COMPONENT::Family());
}

template <typename C1, typename C2, typename... COMPONENT>
inline void GetMask(std::bitset<MAX_COMPONENTS> &mask) {
    mask.set(C1::family());
    GetMask<C2, COMPONENT...>(mask);
}

template <class ENTITY>
template <typename... COMPONENT>
inline typename EntityManager<ENTITY>::template View<COMPONENT...>
EntityManager<ENTITY>::GetByComponents(
    ComponentHandle<COMPONENT, ENTITY> &...components) {
    std::bitset<MAX_COMPONENTS> mask;
    GetMask<COMPONENT...>(mask);
    return View<COMPONENT...>(*this, mask, components...);
}

template <class ENTITY>
inline void EntityManager<ENTITY>::Reset(uint32_t id) {
    ENTITY *entity = m_entites_allocated.at(id);
    std::size_t comp_size = m_components_entites.size();
    for (std::size_t i = 0; i < comp_size; ++i) {
        if (m_components_entites[i] != nullptr) {
            m_components_entites[i]->Erase<VComponent<ENTITY>>(id);
        }
    }
    m_entites_component_masks.at(id).reset();
    delete entity;
    m_entites_allocated[id] = nullptr;
}

template <class ENTITY>
template <typename COMPONENT>
inline void EntityManager<ENTITY>::CheckComponent() {
    Family family = COMPONENT::Family();
    if (m_components_entites.size() <= family) {
        m_components_entites.resize(family + 1, nullptr);
    }

    if (m_components_entites[family] == nullptr) {
        utils::memory::Pool<COMPONENT> *pool =
            new utils::memory::Pool<COMPONENT>;
        pool->Resize(m_entites_allocated.size());
        m_components_entites[family] = pool;
    }
}

template <class ENTITY>
template <typename... COMPONENT>
EntityManager<ENTITY>::View<COMPONENT...>::View(
    EntityManager<ENTITY> &manager, const std::bitset<MAX_COMPONENTS> &mask,
    ComponentHandle<COMPONENT, ENTITY> &...components)
    : m_manager(manager),
      m_mask(mask),
      m_handles(
          std::tuple<ComponentHandle<COMPONENT, ENTITY> &...>(components...)) {
    UnpackManager<0, COMPONENT...>();
}

template <class ENTITY>
template <typename... COMPONENT>
inline typename EntityManager<ENTITY>::template View<COMPONENT...>::Iterator
EntityManager<ENTITY>::View<COMPONENT...>::Begin() {
    Container::iterator begin = m_manager.m_entities_index.begin();
    Container::iterator end = m_manager.m_entities_index.end();
    for (; begin != end; ++begin) {
        uint32_t index = *begin;
        if ((m_manager.m_entites_component_masks[index] & m_mask) == m_mask) {
            UnpackID<0, COMPONENT...>(index);
            break;
        }
    }
    return Iterator(*this, begin, end);
}

template <class ENTITY>
template <typename... COMPONENT>
inline typename EntityManager<ENTITY>::template View<COMPONENT...>::Iterator
EntityManager<ENTITY>::View<COMPONENT...>::End() {
    return Iterator(*this, m_manager.m_entities_index.end(),
                    m_manager.m_entities_index.end());
}

template <class ENTITY>
template <typename... COMPONENT>
template <int N, typename C>
inline void EntityManager<ENTITY>::View<COMPONENT...>::UnpackID(
    std::uint32_t id) {
    std::get<N>(m_handles).m_entity_id = id;
}

template <class ENTITY>
template <typename... COMPONENT>
template <int N, typename C0, typename C1, typename... Cx>
inline void EntityManager<ENTITY>::View<COMPONENT...>::UnpackID(
    std::uint32_t id) {
    UnpackID<N, C0>(id);
    UnpackID<N + 1, C1, Cx...>(id);
}

template <class ENTITY>
template <typename... COMPONENT>
template <int N, typename C>
inline void EntityManager<ENTITY>::View<COMPONENT...>::UnpackManager() {
    std::get<N>(m_handles).m_manager = &m_manager;
}

template <class ENTITY>
template <typename... COMPONENT>
template <int N, typename C0, typename C1, typename... Cx>
inline void EntityManager<ENTITY>::View<COMPONENT...>::UnpackManager() {
    UnpackManager<N, C0>();
    UnpackManager<N + 1, C1, Cx...>();
}

template <class ENTITY>
template <typename... COMPONENT>
EntityManager<ENTITY>::View<COMPONENT...>::Iterator::Iterator(
    View &view, EntityManager<ENTITY>::Container::iterator it,
    EntityManager<ENTITY>::Container::iterator it_end)
    : m_view(view), m_iter(it), m_iter_end(it_end) {}

template <class ENTITY>
template <typename... COMPONENT>
typename EntityManager<ENTITY>::template View<COMPONENT...>::Iterator &
EntityManager<ENTITY>::View<COMPONENT...>::Iterator::operator++() {
    ++m_iter;
    while (m_iter != m_iter_end) {
        std::uint32_t index = *m_iter;
        if (m_view.m_manager.m_entites_allocated.at(index) != nullptr &&
            (m_view.m_manager.m_entites_component_masks.at(index) &
             m_view.m_mask) == m_view.m_mask) {
            m_view.UnpackID<0, COMPONENT...>(index);
            break;
        }
        ++m_iter;
    }
    return *this;
}

template <class ENTITY>
template <typename... COMPONENT>
inline ENTITY *EntityManager<ENTITY>::View<COMPONENT...>::Iterator::operator*()
    const {
    if (m_iter == m_iter_end) return nullptr;
    return m_view.m_manager.m_entites_allocated.at(*m_iter);
}

template <class ENTITY>
template <typename... COMPONENT>
inline ENTITY *EntityManager<ENTITY>::View<COMPONENT...>::Iterator::operator->()
    const {
    if (m_iter == m_iter_end) return nullptr;
    return m_view.m_manager.m_entites_allocated.at(*m_iter);
}

template <class ENTITY>
template <typename... COMPONENT>
bool EntityManager<ENTITY>::View<COMPONENT...>::Iterator::operator==(
    const EntityManager<ENTITY>::View<COMPONENT...>::Iterator &other) const {
    return m_iter == other.m_iter && m_view.m_mask == other.m_view.m_mask &&
           &(m_view.m_manager) == &(other.m_view.m_manager);
}

template <class ENTITY>
template <typename... COMPONENT>
bool EntityManager<ENTITY>::View<COMPONENT...>::Iterator::operator!=(
    const EntityManager<ENTITY>::View<COMPONENT...>::Iterator &other) const {
    return m_iter != other.m_iter || m_view.m_mask != other.m_view.m_mask ||
           &(m_view.m_manager) != &(other.m_view.m_manager);
}

}  // namespace es
}  // namespace foggy

#endif /* ENTITYMANAGER_H */
