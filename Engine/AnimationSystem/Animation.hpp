#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
namespace foggy {
namespace as {

class Animation {
   public:
    Animation();
    ~Animation();

    Animation &addFrame(const sf::Texture *texture);

    std::size_t size() const;
    const sf::Texture *getFrame(std::size_t index) const;

   private:
    friend class AnimatedSprite;
    std::vector<const sf::Texture *> m_frames;
};

}  // namespace as
}  // namespace foggy

#endif /* ANIMATION_HPP */
