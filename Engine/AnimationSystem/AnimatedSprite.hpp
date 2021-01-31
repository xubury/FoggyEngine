#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <functional>
#include <sol/sol.hpp>
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
    FuncType onFinished;
    enum Status { Stopped, Pasued, Playing };

    AnimatedSprite(Animation *animation = nullptr, Status status = Playing,
                   const sf::Time &delta_time = sf::milliseconds(100),
                   bool loop = true, int repeat = 0);

    ~AnimatedSprite();

    void setAnimation(Animation *animation);
    Animation *getAnimation() const;

    void setFrameTime(const sf::Time &delta_time);
    sf::Time getFrameTime() const;

    void setLoop(bool loop);
    bool getLoop() const;

    void setRepeat(int repeat);
    int getRepeat() const;

    void play();
    void pause();
    void stop();
    Status getStatus() const;

    void setCurrentFrame(std::size_t index);
    void setColor(const sf::Color &color);
    void update(const sf::Time &delta_time);

   private:
    Animation *m_animation;
    Status m_status;
    sf::Time m_delta_time;
    sf::Time m_time_elapsed;

    bool m_loop;
    int m_repeat;
    std::size_t m_current_frame;
    sf::Vertex m_vertices[4];

    const sf::Texture *m_texture;
    void setFrame(std::size_t index, bool reset_time);
    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const override;
};
}  // namespace as
}  // namespace foggy

#endif /* ANIMATEDSPRITE_H */
