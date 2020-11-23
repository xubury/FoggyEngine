#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
namespace foggy {
namespace as {

class Animation {
   public:
    Animation(sf::Texture *texture);
    ~Animation();

    void SetTexture(sf::Texture *texture);
    sf::Texture *GetTexture() const;

    Animation &AddFrame(const sf::IntRect &rect);
    Animation &AddFrameRow(int number_x, int number_y, int row);
    Animation &AddFrameColoumn(int number_x, int number_y, int col);

    std::size_t Size() const;
    const sf::IntRect &GetRect(std::size_t index) const;

   private:
    friend class AnimatedSprite;
    std::vector<sf::IntRect> m_frames;
    sf::Texture *m_texture;
};

}  // namespace as
}  // namespace foggy

#endif /* ANIMATION_H */
