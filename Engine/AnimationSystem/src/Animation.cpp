#include <AnimationSystem/Animation.hpp>

namespace foggy {
namespace as {
Animation::Animation(sf::Texture *texture) : m_texture(texture) {}

Animation::~Animation() {}

void Animation::setTexture(sf::Texture *texture) { m_texture = texture; }

sf::Texture *Animation::getTexture() const { return m_texture; }

Animation &Animation::addFrame(const sf::IntRect &rect) {
    m_frames.emplace_back(rect);
    return *this;
}

Animation &Animation::addFrameRow(int number_x, int number_y, int row) {
    const sf::Vector2u size = m_texture->getSize();
    const float delta_x = size.x / float(number_x);
    const float delta_y = size.y / float(number_y);

    for (int i = 0; i < number_x; ++i) {
        addFrame(sf::IntRect(i * delta_x, row * delta_y, delta_x, delta_y));
    }
    return *this;
}

Animation &Animation::addFrameColumn(int number_x, int number_y, int col) {
    const sf::Vector2u size = m_texture->getSize();
    const float delta_x = size.x / float(number_x);
    const float delta_y = size.y / float(number_y);

    for (int i = 0; i < number_x; ++i) {
        addFrame(sf::IntRect(col * delta_x, i * delta_y, delta_x, delta_y));
    }
    return *this;
}

Animation &Animation::addFrameSheet(int start, int end, int number_x,
                                    int number_y, int x_offset, int y_offset) {
    const sf::Vector2u size = m_texture->getSize();
    const float delta_x = (size.x - x_offset) / float(number_x);
    const float delta_y = (size.y - y_offset) / float(number_y);
    for (int i = start; i <= end; ++i) {
        const int row = i / number_x;
        const int col = i % number_x;
        addFrame(sf::IntRect(col * delta_x, row * delta_y, delta_x, delta_y));
    }
    return *this;
}

std::size_t Animation::size() const { return m_frames.size(); }

const sf::IntRect &Animation::getRect(std::size_t index) const {
    return m_frames[index];
}

}  // namespace as
}  // namespace foggy
