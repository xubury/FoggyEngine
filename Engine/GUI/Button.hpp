#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <functional>

#include "GUI/Label.hpp"
#include "GUI/Widget.hpp"

namespace foggy {

class Button : public Widget {
   public:
    using FuncType = std::function<void(const sf::Event& event, Button& self)>;
    static FuncType DefaultFunc;
    Button(Widget* parent = nullptr);
    virtual ~Button() = default;
    FuncType OnClick;

   protected:
    virtual bool ProcessEvent(const sf::Event& event,
                              const sf::Vector2f& parent_pos);

    virtual void OnMouseEntered();
    virtual void OnMouseLeft();

   private:
    enum Status { None = 0, Hover = 1 };
    Status m_status;
};

class TextButton : public Button {
   public:
    TextButton(const std::string& text, const sf::Color& fill,
               const sf::Color& outline, float outline_thickness,
               const sf::Font& font, const sf::Color& color,
               Widget* parent = nullptr);
    virtual ~TextButton() = default;
    void SetText(const std::string& text);
    void SetCharacterSize(uint32_t size);
    void SetTextColor(const sf::Color& color);
    void SetFillColor(const sf::Color& color);
    void SetOutlineColor(const sf::Color& color);
    void SetOutlineThickness(float thickness);
    virtual sf::Vector2f GetSize() const override;

   private:
    sf::RectangleShape m_shape;
    Label m_label;
    void UpdateShape() override;
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;
    sf::Color m_fill_color;
    sf::Color m_outline_color;
    virtual void OnMouseEntered() override;
    virtual void OnMouseLeft() override;
};

}  // namespace foggy

#endif /* BUTTON_H */
