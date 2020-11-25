#include <AnimationSystem/AnimatedSprite.hpp>
#include <cassert>
#include <iostream>

namespace foggy {
namespace as {
AnimatedSprite::AnimatedSprite(Animation *animation, Status status,
                               const sf::Time &delta_time, bool loop,
                               int repeat)
    : m_status(status),
      m_delta_time(delta_time),
      m_loop(loop),
      m_repeat(repeat) {
    SetAnimation(animation);
}

void AnimatedSprite::SetAnimation(Animation *animation) {
    if (m_animation != animation) {
        m_animation = animation;
        m_time_elapsed = sf::Time::Zero;
        m_current_frame = 0;
        SetFrame(0, true);
    }
}

Animation *AnimatedSprite::GetAnimation() const { return m_animation; }

void AnimatedSprite::SetFrameTime(const sf::Time &delta_time) {
    m_delta_time = delta_time;
}

sf::Time AnimatedSprite::GetFrameTime() const { return m_delta_time; }

void AnimatedSprite::SetLoop(bool loop) { m_loop = loop; }

bool AnimatedSprite::GetLoop() const { return m_loop; }

void AnimatedSprite::SetRepeat(int repeat) { m_repeat = repeat; }

int AnimatedSprite::GetRepeat() const { return m_repeat; }

void AnimatedSprite::Play() { m_status = AnimatedSprite::Playing; }

void AnimatedSprite::Pause() { m_status = AnimatedSprite::Pasued; }

void AnimatedSprite::Stop() {
    m_status = AnimatedSprite::Stopped;
    m_current_frame = 0;
    SetFrame(0, true);
}

AnimatedSprite::Status AnimatedSprite::GetStatus() const { return m_status; }

void AnimatedSprite::SetFrame(std::size_t index) {
    assert(m_animation != nullptr);
    m_current_frame = index % m_animation->Size();
    SetFrame(index, true);
}

void AnimatedSprite::SetColor(const sf::Color &color) {
    m_vertices[0].color = color;
    m_vertices[1].color = color;
    m_vertices[2].color = color;
    m_vertices[3].color = color;
}

void AnimatedSprite::Update(const sf::Time &delta_time) {
    if (m_status == Playing && m_animation != nullptr) {
        m_time_elapsed += delta_time;
        if (m_time_elapsed > m_delta_time) {
            m_time_elapsed -= m_delta_time;
            if (m_current_frame + 1 < m_animation->Size()) {
                ++m_current_frame;
            } else {
                m_current_frame = 0;
                if (!m_loop) {
                    --m_repeat;
                    if (m_repeat <= 0) {
                        m_status = Stopped;
                        if (!OnFinishd.empty() && OnFinishd.top() != nullptr) {
                            auto &func = OnFinishd.top();
                            func();
                            OnFinishd.pop();
                        }
                    }
                }
            }
        }
        SetFrame(m_current_frame, false);
    }
}

void AnimatedSprite::SetFrame(std::size_t index, bool reset_time) {
    if (m_animation != nullptr) {
        sf::IntRect rect = m_animation->GetRect(index);

        m_vertices[0].position =
            sf::Vector2f(-(float)rect.width / 2, -(float)rect.height / 2);
        m_vertices[1].position =
            sf::Vector2f(-(float)rect.width / 2, (float)rect.height / 2);
        m_vertices[2].position =
            sf::Vector2f((float)rect.width / 2, (float)rect.height / 2);
        m_vertices[3].position =
            sf::Vector2f((float)rect.width / 2, -(float)rect.height / 2);

        float left = (float)rect.left;
        float right = left + (float)rect.width;
        float top = (float)rect.top;
        float bottom = top + (float)rect.height;

        m_vertices[0].texCoords = sf::Vector2f(left, top);
        m_vertices[1].texCoords = sf::Vector2f(left, bottom);
        m_vertices[2].texCoords = sf::Vector2f(right, bottom);
        m_vertices[3].texCoords = sf::Vector2f(right, top);
    }
    if (reset_time) {
        m_time_elapsed = sf::Time::Zero;
    }
}

void AnimatedSprite::draw(sf::RenderTarget &target,
                          sf::RenderStates states) const {
    if (m_animation != nullptr && m_animation->m_texture != nullptr) {
        states.transform *= getTransform();
        states.texture = m_animation->m_texture;
        target.draw(m_vertices, 4, sf::Quads, states);
    }
}

}  // namespace as
}  // namespace foggy
