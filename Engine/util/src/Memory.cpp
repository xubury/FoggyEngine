#include <util/Memory.hpp>
namespace foggy {
namespace utils {

namespace memory {

std::size_t VPool::Size() const { return m_memory.size(); }

void VPool::Resize(std::size_t size) { m_memory.resize(size, nullptr); }

bool VPool::IsSet(std::size_t index) const {
    return m_memory.at(index) != nullptr;
}

}  // namespace memory

}  // namespace utils
}  // namespace foggy
