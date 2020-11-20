#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
namespace foggy {
namespace utils {
namespace memory {

class VPool {
   public:
    VPool(const VPool&) = delete;
    VPool& operator=(const VPool&) = delete;

    VPool(VPool&&) = default;
    VPool& operator=(VPool&&) = default;

    VPool() = default;
    virtual ~VPool() = default;

    std::size_t Size() const;
    void Resize(std::size_t size);

    bool IsSet(std::size_t index) const;

    template <typename T>
    T& At(std::size_t index) const;

    template <typename T>
    void Erase(std::size_t index);

    template <typename T, typename... ARGS>
    void Emplace(std::size_t index, ARGS&&... args);

    template <typename T>
    class Iterator {
       public:
        Iterator(std::size_t index, const VPool& pool);

        bool operator!=(const Iterator<T>& other);
        void operator++();
        T& operator*() const;
        T& Data() const;
        std::size_t Index() const;

       private:
        std::size_t m_index;
        const VPool& m_pool;
    };

   protected:
    template <typename T>
    friend class Iterator;
    std::vector<void*> m_memory;
};

template <typename T>
class Pool : public VPool {
   public:
    Pool(const Pool&) = delete;
    Pool& operator=(const Pool&) = delete;

    Pool(Pool&&) = default;
    Pool& operator=(Pool&&) = default;

    Pool() = default;
    virtual ~Pool();

    T& At(std::size_t index) const;

    void Erase(std::size_t index);

    template <typename... ARGS>
    void Emplace(std::size_t index, ARGS&&... args);

    VPool::Iterator<T> Begin() const;
    VPool::Iterator<T> End() const;
};

template <typename T>
T& VPool::At(std::size_t index) const {
    return *static_cast<T*>(m_memory.at(index));
}

template <typename T>
void VPool::Erase(std::size_t index) {
    delete static_cast<T*>(m_memory.at(index));
    m_memory[index] = nullptr;
}

template <typename T, typename... Args>
void VPool::Emplace(std::size_t index, Args&&... args) {
    delete static_cast<T*>(m_memory.at(index));
    m_memory[index] = new T(args...);
}

template <typename T>
VPool::Iterator<T>::Iterator(std::size_t index, const VPool& pool)
    : m_index(index), m_pool(pool) {}

template <typename T>
bool VPool::Iterator<T>::operator!=(const Iterator<T>& other) {
    return m_index != other._index || &m_pool != &other._pool;
}

template <typename T>
void VPool::Iterator<T>::operator++() {
    auto size = m_pool.m_memory.size();
    ++m_index;
    while (m_index < size || m_pool.m_memory[m_index] == nullptr) ++m_index;
}

template <typename T>
T& VPool::Iterator<T>::operator*() const {
    return m_pool.At<T>(m_index);
}

template <typename T>
T& VPool::Iterator<T>::Data() const {
    return m_pool.At<T>(m_index);
}

template <typename T>
std::size_t VPool::Iterator<T>::Index() const {
    return m_index;
}

template <typename T>
T& Pool<T>::At(std::size_t index) const {
    return VPool::At<T>(index);
}

template <typename T>
void Pool<T>::Erase(std::size_t index) {
    VPool::Erase<T>(index);
}

template <typename T>
template <typename... Args>
void Pool<T>::Emplace(std::size_t index, Args&&... args) {
    VPool::Emplace<T>(index, args...);
}

template <typename T>
Pool<T>::~Pool() {
    const std::size_t size = m_memory.size();
    for (std::size_t i = 0; i < size; ++i) delete static_cast<T*>(m_memory[i]);
    m_memory.clear();
}

template <typename T>
VPool::Iterator<T> Pool<T>::Begin() const {
    std::size_t index = 0;
    std::size_t size = m_memory.size();

    while (index < size and m_memory[index] == nullptr) ++index;

    return VPool::Iterator<T>(index, *this);
}

template <typename T>
VPool::Iterator<T> Pool<T>::End() const {
    return VPool::Iterator<T>(m_memory.size(), *this);
}

}  // namespace memory
}  // namespace utils
}  // namespace foggy

#endif /* MEMORY_H */
