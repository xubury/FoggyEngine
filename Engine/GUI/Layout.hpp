#ifndef LAYOUT_H
#define LAYOUT_H

#include <vector>

#include "GUI/Widget.hpp"

namespace foggy {

class Layout : protected Widget {
   public:
    Layout(Widget *parent = nullptr);
    virtual ~Layout() = default;

    void SetSpace(float pixel);

   protected:
    friend class Container;
    float m_space;
};

class VLayout : public Layout {
   public:
    VLayout(const VLayout &) = delete;
    VLayout &operator=(const VLayout &) = delete;
    VLayout(Widget *parent = nullptr);
    ~VLayout();

    void Add(Widget *widget);
    Widget *At(uint32_t index);
    virtual sf::Vector2f GetSize() const override;

   protected:
    virtual bool ProcessEvent(const sf::Event &event,
                              const sf::Vector2f &parent_pos) override;
    virtual void ProcessEvents(const sf::Vector2f &parent_pos) override;

   private:
    std::vector<Widget *> m_widgets;
    virtual void UpdateShape() override;
    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const override;
};

}  // namespace foggy

#endif /* LAYOUT_H */
