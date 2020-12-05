#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <memory>
#include <unordered_map>

#include "EntitySystem/Defines.hpp"
#include "EntitySystem/ES.hpp"
#include "Lua/utils.hpp"
/* Code Snippet(How to iterate over table):
 * lua_pushnil(L);
 * for (; lua_next(L, -2) != 0; lua_pop(L, 1)) {
 * if (!lua_istable(L, -1)) continue;
 * do something..
 * } */
namespace foggy {

class VLuaHandler {
   public:
    VLuaHandler(const VLuaHandler &) = delete;
    VLuaHandler &operator=(const VLuaHandler &) = delete;
    virtual void InitComponent(es::EntityManager<es::DefaultEntity> *manager,
                               int id, const std::string &filename) = 0;

    VLuaHandler() = default;
    virtual ~VLuaHandler() = default;

   protected:
    static uint32_t s_id_counter;
};

template <typename T>
class LuaHandler : public VLuaHandler {
   public:
    LuaHandler(const LuaHandler &) = delete;
    LuaHandler &operator=(const LuaHandler &) = delete;

    static uint32_t ID();

   protected:
    LuaHandler() = default;
};

class LuaManager {
   public:
    LuaManager(const LuaManager &) = delete;
    LuaManager &operator=(const LuaManager &) = delete;

    ~LuaManager() = default;

    static LuaManager &Instance() {
        static LuaManager s_instance;
        return s_instance;
    }

    template <typename T>
    bool Add(std::shared_ptr<T> ptr);

    template <typename T, typename... Args>
    bool Add(Args &&...args);

    template <typename T>
    T *Lua();

   private:
    LuaManager() = default;

   private:
    std::unordered_map<uint32_t, std::shared_ptr<VLuaHandler>> m_lua_tables;
};

template <typename T>
uint32_t LuaHandler<T>::ID() {
    static uint32_t id = VLuaHandler::s_id_counter++;
    return id;
}

template <typename T>
T *LuaManager::Lua() {
    return std::static_pointer_cast<T>(m_lua_tables.at(T::ID())).get();
}
template <typename T>
bool LuaManager::Add(std::shared_ptr<T> ptr) {
    if (m_lua_tables.count(T::ID()) == 0) {
        m_lua_tables.insert(std::make_pair(T::ID(), ptr));
        return true;
    }
    return false;
}

template <typename T, typename... Args>
bool LuaManager::Add(Args &&...args) {
    if (m_lua_tables.count(T::ID()) == 0) {
        m_lua_tables.emplace(
            T::ID(), std::shared_ptr<T>(new T(std::forward<Args>(args)...)));
        return true;
    }
    return false;
}

}  // namespace foggy

#endif /* HANDLER_H */
