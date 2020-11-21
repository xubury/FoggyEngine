#ifndef SYSTEM_H
#define SYSTEM_H

#include <SFML/System.hpp>
#include <cassert>
#include <memory>
#include <unordered_map>

#include "EntitySystem/Defines.hpp"

namespace foggy {
namespace es {

template <typename ENTITY>
class EntityManager;
template <typename ENTITY>
class Entity;

template <typename ENTITY>
class VSystem {
   public:
    VSystem(const VSystem&) = delete;
    VSystem& operator=(const VSystem&) = delete;

    virtual ~VSystem() = default;

    virtual void Update(EntityManager<ENTITY>& entity_manager,
                        const sf::Time& deltaTime) = 0;

   protected:
    VSystem() = default;
    static Family s_family_counter;
};

template <typename COMPONENT, typename ENTITY>
class System : public VSystem<ENTITY> {
   public:
    System(const System&) = delete;
    System& operator=(const System&) = delete;

    System() = default;
    virtual ~System() = default;

    static Family Family();
};

#define ES_INIT_VSYSTEM(ENTITY) \
    template <>                 \
    foggy::es::Family foggy::es::VSystem<ENTITY>::s_family_counter = 0;

template <typename ENTITY>
class SystemManager {
   public:
    SystemManager(const SystemManager&) = delete;
    SystemManager& operator=(const SystemManager&) = delete;

    SystemManager(EntityManager<ENTITY>& manager);
    ~SystemManager() = default;

    template <typename SYSTEM>
    bool Add(std::shared_ptr<SYSTEM> ptr);

    template <typename SYSTEM, typename... Args>
    bool Add(Args&&... args);

    template <typename SYSTEM>
    bool Remove();

    template <typename SYSTEM>
    std::shared_ptr<SYSTEM> System();

    template <typename SYSTEM>
    void Update(const sf::Time& deltaTime);

    void UpdateAll(const sf::Time& deltaTime);

   private:
    EntityManager<ENTITY>& m_manager;
    std::unordered_map<Family, std::shared_ptr<VSystem<ENTITY>>> m_systems;
};

template <typename COMPONENT, typename ENTITY>
Family System<COMPONENT, ENTITY>::Family() {
    static ::foggy::es::Family family = VSystem<ENTITY>::s_family_counter++;
    assert(family < MAX_COMPONENTS);
    return family;
}

template <typename ENTITY>
SystemManager<ENTITY>::SystemManager(EntityManager<ENTITY>& manager)
    : m_manager(manager) {}

template <typename ENTITY>
void SystemManager<ENTITY>::UpdateAll(const sf::Time& deltaTime) {
    for (auto& pair : m_systems) pair.second->Update(m_manager, deltaTime);
}

template <typename ENTITY>
template <typename SYSTEM>
bool SystemManager<ENTITY>::Add(std::shared_ptr<SYSTEM> ptr) {
    if (m_systems.count(SYSTEM::Family()) == 0) {
        m_systems.insert(std::make_pair(SYSTEM::Family(), ptr));
        return true;
    }
    return false;
}

template <typename ENTITY>
template <typename SYSTEM, typename... Args>
bool SystemManager<ENTITY>::Add(Args&&... args) {
    if (m_systems.count(SYSTEM::Family()) == 0) {
        m_systems.emplace(
            SYSTEM::Family(),
            std::shared_ptr<SYSTEM>(new SYSTEM(std::forward<Args>(args)...)));
        return true;
    }
    return false;
}

template <typename ENTITY>
template <typename SYSTEM>
bool SystemManager<ENTITY>::Remove() {
    if (m_systems.count(SYSTEM::Family()) == 0) return false;
    m_systems.erase(SYSTEM::Family());
    return true;
}

template <typename ENTITY>
template <typename SYSTEM>
inline std::shared_ptr<SYSTEM> SystemManager<ENTITY>::System() {
    return std::static_pointer_cast<SYSTEM>(m_systems.at(SYSTEM::Family()));
}

template <typename ENTITY>
template <typename SYSTEM>
inline void SystemManager<ENTITY>::Update(const sf::Time& deltaTime) {
    System<SYSTEM>()->Update(m_manager, deltaTime);
}

}  // namespace es
}  // namespace foggy

#endif /* SYSTEM_H */
