#include <Utils/Memory.hpp>
namespace foggy {
namespace utils {

namespace memory {

std::size_t VPool::size() const { return m_memory.size(); }

void VPool::resize(std::size_t size) { m_memory.resize(size, nullptr); }

bool VPool::isSet(std::size_t index) const {
    return m_memory.at(index) != nullptr;
}

}  // namespace memory

}  // namespace utils
}  // namespace foggy
