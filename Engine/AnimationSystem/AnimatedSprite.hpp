#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <functional>
#include <stack>

#include "AnimationSystem/Animation.hpp"
namespace foggy {
namespace as {

class AnimatedSprite : public sf::Drawable, public sf::Transformable {
   public:
    AnimatedSprite(const AnimatedSprite &) = default;
    AnimatedSprite &operator=(const AnimatedSprite &) = default;

    AnimatedSprite(AnimatedSprite &&) = default;
    AnimatedSprite &operator=(AnimatedSprite &&) = default;

    using FuncType = std::function<void()>;
    static FuncType default_func;
    std::stack<FuncType> OnFinishd;
    enum Status { Stopped, Pasued, Playing };

    AnimatedSprite(Animation *animation = nullptr, Status status = Playing,
                   const sf::Time &delta_time = sf::milliseconds(100),
                   bool loop = true, int repeat = 0);

    void SetAnimation(Animation *animation);
    Animation *GetAnimation() const;

    void SetFrameTime(const sf::Time &delta_time);
    sf::Time GetFrameTime() const;

    void SetLoop(bool loop);
    bool GetLoop() const;

    void SetRepeat(int repeat);
    int GetRepeat() const;

    void Play();
    void Pause();
    void Stop();
    Status GetStatus() const;

    void SetFrame(std::size_t index);
    void SetColor(const sf::Color &color);
    void Update(const sf::Time &delta_time);

   private:
    Animation *m_animation;
    Status m_status;
    sf::Time m_delta_time;
    sf::Time m_time_elapsed;

    bool m_loop;
    int m_repeat;
    std::size_t m_current_frame;
    sf::Vertex m_vertices[4];

    void SetFrame(std::size_t index, bool reset_time);
    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const override;
};
}  // namespace as
}  // namespace foggy

#endif /* ANIMATEDSPRITE_H */
