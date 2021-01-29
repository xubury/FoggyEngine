#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "GUI/Widget.hpp"

namespace foggy {
namespace gui {

class Sprite : virtual public Widget {
   public:
    Sprite(const Sprite &) = delete;
    Sprite &operator=(const Sprite &) = delete;

    Sprite(const sf::Texture &texture, Widget *parent = nullptr);
    virtual ~Sprite();

    void setTexture(const sf::Texture &texture, bool reset_rect = false);
    void SetTextureRect(const sf::IntRect &rect);

    virtual void setColor(const sf::Color &color);

    virtual sf::Vector2f getSize() const override;

    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const override;

   private:
    sf::Sprite m_sprite;
    sf::Color m_color;
};

}  // namespace gui
}  // namespace foggy

#endif /* SPRITE_H */
