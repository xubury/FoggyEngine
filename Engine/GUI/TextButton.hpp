#ifndef TEXTBUTTON_HPP
#define TEXTBUTTON_HPP

#include "GUI/Button.hpp"

namespace foggy {
namespace gui {

class TextButton : public Button {
   public:
    TextButton(const std::string& text, const sf::Color& fill,
               const sf::Color& outline, float outline_thickness,
               const sf::Font& font, const sf::Color& color,
               Widget* parent = nullptr);
    virtual ~TextButton() = default;
    void setText(const std::string& text);
    void setCharacterSize(uint32_t size);
    void setTextColor(const sf::Color& color);
    void setFillColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);
    virtual sf::Vector2f getSize() const override;

   private:
    sf::RectangleShape m_shape;
    Label m_label;
    void updateShape() override;
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;
    sf::Color m_fill_color;
    sf::Color m_outline_color;
    float m_outline_thickness;
    virtual void onMouseEntered() override;
    virtual void onMouseLeft() override;
};

}  // namespace gui
}  // namespace foggy

#endif /* TEXTBUTTON_HPP */