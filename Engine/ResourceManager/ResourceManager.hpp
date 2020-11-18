#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <memory>
#include <stdexcept>
#include <unordered_map>

namespace foggy {

template <typename RESOURCE, typename IDENTIFIER = int>
class ResourceManager {
   public:
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;

    ResourceManager() = default;

    template <typename... ARGS>
    void Load(const IDENTIFIER &id, ARGS &&...args);

    bool Count(const IDENTIFIER &id);

    RESOURCE &Get(const IDENTIFIER &id);

    template <typename... ARGS>
    RESOURCE &GetOrLoad(const IDENTIFIER &id, ARGS &&...args);

   private:
    std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> m_map;
};

template <typename RESOURCE, typename IDENTIFIER>
template <typename... ARGS>
void ResourceManager<RESOURCE, IDENTIFIER>::Load(const IDENTIFIER &id,
                                                 ARGS &&...args) {
    std::unique_ptr<RESOURCE> ptr(new RESOURCE);
    if (!ptr->loadFromFile(std::forward<ARGS>(args)...)) {
        throw std::runtime_error("Cannot load from file");
    }
    if (m_map.emplace(id, std::move(ptr)).second == false) {
        throw std::runtime_error(
            "Fail to implace in map, object already loaded.");
    }
}

template <typename RESOURCE, typename IDENTIFIER>
RESOURCE &ResourceManager<RESOURCE, IDENTIFIER>::Get(const IDENTIFIER &id) {
    return *m_map.at(id);
}

}  // namespace foggy
#endif /* RESOURCE_MANAGER */
