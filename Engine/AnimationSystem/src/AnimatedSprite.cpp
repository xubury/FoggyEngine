#include <AnimationSystem/AnimatedSprite.hpp>
#include <cassert>
#include <iostream>

namespace foggy {
namespace as {
AnimatedSprite::FuncType AnimatedSprite::default_func;

AnimatedSprite::AnimatedSprite(Animation *animation, Status status,
                               const sf::Time &delta_time, bool loop,
                               int repeat)
    : onFinished(nullptr),
      m_status(status),
      m_delta_time(delta_time),
      m_loop(loop),
      m_repeat(repeat) {
    setAnimation(animation);
}

AnimatedSprite::~AnimatedSprite() {}

void AnimatedSprite::setAnimation(Animation *animation) {
    if (m_animation != animation) {
        m_animation = animation;
        m_time_elapsed = sf::Time::Zero;
        m_current_frame = 0;
        setFrame(0, true);
    }
}

Animation *AnimatedSprite::getAnimation() const { return m_animation; }

void AnimatedSprite::setFrameTime(const sf::Time &delta_time) {
    m_delta_time = delta_time;
}

sf::Time AnimatedSprite::getFrameTime() const { return m_delta_time; }

void AnimatedSprite::setLoop(bool loop) { m_loop = loop; }

bool AnimatedSprite::getLoop() const { return m_loop; }

void AnimatedSprite::setRepeat(int repeat) { m_repeat = repeat; }

int AnimatedSprite::getRepeat() const { return m_repeat; }

void AnimatedSprite::play() { m_status = AnimatedSprite::Playing; }

void AnimatedSprite::pause() { m_status = AnimatedSprite::Pasued; }

void AnimatedSprite::stop() {
    m_status = AnimatedSprite::Stopped;
    m_current_frame = 0;
    setFrame(0, true);
}

AnimatedSprite::Status AnimatedSprite::getStatus() const { return m_status; }

void AnimatedSprite::setCurrentFrame(std::size_t index) {
    assert(m_animation != nullptr);
    m_current_frame = index % m_animation->size();
    setFrame(index, true);
}

void AnimatedSprite::setColor(const sf::Color &color) {
    m_vertices[0].color = color;
    m_vertices[1].color = color;
    m_vertices[2].color = color;
    m_vertices[3].color = color;
}

void AnimatedSprite::update(const sf::Time &delta_time) {
    if (m_status == Playing && m_animation != nullptr) {
        m_time_elapsed += delta_time;
        if (m_time_elapsed > m_delta_time) {
            m_time_elapsed -= m_delta_time;
            if (m_current_frame + 1 < m_animation->size()) {
                ++m_current_frame;
            } else {
                m_current_frame = 0;
                if (!m_loop) {
                    --m_repeat;
                    if (m_repeat <= 0) {
                        m_status = Stopped;
                        if (onFinished != nullptr) {
                            onFinished();
                        }
                        // if (!OnFinishd.empty() && OnFinishd.top() != nullptr)
                        // {
                        //     auto &func = OnFinishd.top();
                        //     func();
                        //     OnFinishd.pop();
                        // }
                    }
                }
            }
        }
        setFrame(m_current_frame, false);
    }
}

void AnimatedSprite::setFrame(std::size_t index, bool reset_time) {
    if (m_animation != nullptr) {
        m_texture = m_animation->getFrame(index);
        float width = m_texture->getSize().x;
        float height = m_texture->getSize().y;
        m_vertices[0].position = sf::Vector2f(-width / 2, -height / 2);
        m_vertices[1].position = sf::Vector2f(-width / 2, height / 2);
        m_vertices[2].position = sf::Vector2f(width / 2, height / 2);
        m_vertices[3].position = sf::Vector2f(width / 2, -height / 2);

        m_vertices[0].texCoords = sf::Vector2f(0, 0);
        m_vertices[1].texCoords = sf::Vector2f(0, height);
        m_vertices[2].texCoords = sf::Vector2f(width, height);
        m_vertices[3].texCoords = sf::Vector2f(width, 0);
    }
    if (reset_time) {
        m_time_elapsed = sf::Time::Zero;
    }
}

void AnimatedSprite::draw(sf::RenderTarget &target,
                          sf::RenderStates states) const {
    if (m_animation != nullptr && m_texture != nullptr) {
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices, 4, sf::Quads, states);
    }
}

}  // namespace as
}  // namespace foggy
