#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <SFML/Audio.hpp>
#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "AnimationSystem/Animation.hpp"

namespace foggy {

template <typename RESOURCE, typename IDENTIFIER = int>
class ResourceManager {
   public:
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;

    ResourceManager() = default;

    template <typename... ARGS>
    RESOURCE &load(const IDENTIFIER &id, ARGS &&...args);

    bool count(const IDENTIFIER &id);

    RESOURCE &Get(const IDENTIFIER &id);

    template <typename... ARGS>
    RESOURCE &getOrLoad(const IDENTIFIER &id, ARGS &&...args);

    void clear();

   private:
    std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> m_map;
};

/* sf::Music use different load api, so make a special case here */
template <typename IDENTIFIER>
class ResourceManager<sf::Music, IDENTIFIER> {
   public:
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;

    ResourceManager() = default;

    template <typename... ARGS>
    sf::Music &load(const IDENTIFIER &id, ARGS &&...args);

    bool count(const IDENTIFIER &id);

    sf::Music &Get(const IDENTIFIER &id);

    template <typename... ARGS>
    sf::Music &getOrLoad(const IDENTIFIER &id, ARGS &&...args);

    void clear();

   private:
    std::unordered_map<IDENTIFIER, std::unique_ptr<sf::Music>> m_map;
};

/* Animation special case */
template <typename IDENTIFIER>
class ResourceManager<as::Animation, IDENTIFIER> {
   public:
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;

    ResourceManager() = default;

    template <typename... ARGS>
    as::Animation &load(const IDENTIFIER &id, ARGS &&...args);

    bool count(const IDENTIFIER &id);

    as::Animation &Get(const IDENTIFIER &id);

    template <typename... ARGS>
    as::Animation &getOrLoad(const IDENTIFIER &id, ARGS &&...args);

    void clear();

   private:
    std::unordered_map<IDENTIFIER, std::unique_ptr<as::Animation>> m_map;
};

template <typename RESOURCE, typename IDENTIFIER>
template <typename... ARGS>
RESOURCE &ResourceManager<RESOURCE, IDENTIFIER>::load(const IDENTIFIER &id,
                                                      ARGS &&...args) {
    std::unique_ptr<RESOURCE> ptr(new RESOURCE);
    if (!ptr->loadFromFile(std::forward<ARGS>(args)...)) {
        throw std::runtime_error("Cannot load from file");
    }
    if (m_map.emplace(id, std::move(ptr)).second == false) {
        throw std::runtime_error(
            "Fail to implace in map, object already loaded.");
    }
    return *m_map[id];
}

template <typename RESOURCE, typename IDENTIFIER>
RESOURCE &ResourceManager<RESOURCE, IDENTIFIER>::Get(const IDENTIFIER &id) {
    return *m_map.at(id);
}

template <typename RESOURCE, typename IDENTIFIER>
bool ResourceManager<RESOURCE, IDENTIFIER>::count(const IDENTIFIER &id) {
    return m_map.count(id);
}

template <typename RESOURCE, typename IDENTIFIER>
template <typename... ARGS>
RESOURCE &ResourceManager<RESOURCE, IDENTIFIER>::getOrLoad(const IDENTIFIER &id,
                                                           ARGS &&...args) {
    if (m_map.count(id) == 0) {
        return load(id, std::forward<ARGS>(args)...);
    }
    return Get(id);
}

template <typename RESOURCE, typename IDENTIFIER>
void ResourceManager<RESOURCE, IDENTIFIER>::clear() {
    m_map.clear();
}

template <typename IDENTIFIER>
template <typename... ARGS>
sf::Music &ResourceManager<sf::Music, IDENTIFIER>::load(const IDENTIFIER &id,
                                                        ARGS &&...args) {
    std::unique_ptr<sf::Music> ptr(new sf::Music);
    if (!ptr->openFromFile(std::forward<ARGS>(args)...)) {
        throw std::runtime_error("Cannot load from file");
    }
    if (m_map.emplace(id, std::move(ptr)).second == false) {
        throw std::runtime_error(
            "Fail to implace in map, object already loaded.");
    }
    return *m_map[id];
}

template <typename IDENTIFIER>
sf::Music &ResourceManager<sf::Music, IDENTIFIER>::Get(const IDENTIFIER &id) {
    return *m_map.at(id);
}

template <typename IDENTIFIER>
bool ResourceManager<sf::Music, IDENTIFIER>::count(const IDENTIFIER &id) {
    return m_map.count(id);
}

template <typename IDENTIFIER>
template <typename... ARGS>
sf::Music &ResourceManager<sf::Music, IDENTIFIER>::getOrLoad(
    const IDENTIFIER &id, ARGS &&...args) {
    if (m_map.count(id) == 0) {
        return load(id, std::forward<ARGS>(args)...);
    }
    return Get(id);
}

template <typename IDENTIFIER>
void ResourceManager<sf::Music, IDENTIFIER>::clear() {
    m_map.clear();
}

template <typename IDENTIFIER>
template <typename... ARGS>
as::Animation &ResourceManager<as::Animation, IDENTIFIER>::load(
    const IDENTIFIER &id, ARGS &&...args) {
    std::unique_ptr<as::Animation> ptr(
        new as::Animation(std::forward<ARGS>(args)...));
    if (m_map.emplace(id, std::move(ptr)).second == false) {
        throw std::runtime_error(
            "Fail to implace in map, object already loaded.");
    }
    return *m_map[id];
}

template <typename IDENTIFIER>
as::Animation &ResourceManager<as::Animation, IDENTIFIER>::Get(
    const IDENTIFIER &id) {
    return *m_map.at(id);
}

template <typename IDENTIFIER>
bool ResourceManager<as::Animation, IDENTIFIER>::count(const IDENTIFIER &id) {
    return m_map.count(id);
}

template <typename IDENTIFIER>
template <typename... ARGS>
as::Animation &ResourceManager<as::Animation, IDENTIFIER>::getOrLoad(
    const IDENTIFIER &id, ARGS &&...args) {
    if (m_map.count(id) == 0) {
        return load(id, std::forward<ARGS>(args)...);
    }
    return Get(id);
}

template <typename IDENTIFIER>
void ResourceManager<as::Animation, IDENTIFIER>::clear() {
    m_map.clear();
}

}  // namespace foggy
#endif /* RESOURCE_MANAGER */
