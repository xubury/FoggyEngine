#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
namespace foggy {
namespace as {

class Animation {
   public:
    Animation(sf::Texture *texture);
    ~Animation();

    void setTexture(sf::Texture *texture);
    sf::Texture *getTexture() const;

    Animation &addFrame(const sf::IntRect &rect);
    Animation &addFrameRow(int number_x, int number_y, int row);
    Animation &addFrameColumn(int number_x, int number_y, int col);
    Animation &addFrameSheet(int start, int end, int number_x, int number_y,
                             int x_offset, int y_offset);

    std::size_t size() const;
    const sf::IntRect &getRect(std::size_t index) const;

   private:
    friend class AnimatedSprite;
    std::vector<sf::IntRect> m_frames;
    sf::Texture *m_texture;
};

}  // namespace as
}  // namespace foggy

#endif /* ANIMATION_H */
