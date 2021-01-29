#ifndef SPRITEBUTTON_H
#define SPRITEBUTTON_H

#include "GUI/Button.hpp"
#include "GUI/Sprite.hpp"
#include "GUI/Widget.hpp"

namespace foggy {
namespace gui {

class SpriteButton : virtual public Widget, public Button, public Sprite {
   public:
    SpriteButton(const SpriteButton &) = delete;
    SpriteButton &operator=(const SpriteButton &) = delete;

    SpriteButton(const sf::Texture &texture, Widget *parent = nullptr);
    virtual ~SpriteButton();

    void setColor(const sf::Color &color) override;

   private:
    sf::Color m_color;

    virtual void onMouseEntered() override;
    virtual void onMouseLeft() override;

    void updateShape() override;
    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const override;
};

}  // namespace gui

}  // namespace foggy

#endif /* SPRITEBUTTON_H */
