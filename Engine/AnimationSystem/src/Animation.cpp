#include <AnimationSystem/Animation.hpp>

namespace foggy {
namespace as {

Animation::Animation() {}

Animation::~Animation() = default;

Animation &Animation::addFrame(const sf::Texture *texture) {
    m_frames.emplace_back(texture);
    return *this;
}

std::size_t Animation::size() const { return m_frames.size(); }

const sf::Texture *Animation::getFrame(std::size_t index) const {
    return m_frames[index];
}

}  // namespace as
}  // namespace foggy
