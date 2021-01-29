#ifndef GUI_CONFIGURATION_H
#define GUI_CONFIGURATION_H

#include "ActionSystem/ActionMap.hpp"
#include "ResourceManager/ResourceManager.hpp"

namespace foggy {
namespace gui {

class Configuration {
   public:
    Configuration() = delete;
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    enum Fonts { GUI };
    static ResourceManager<sf::Font, int> default_fonts;

    enum GuiInputs { Escape };
    static ActionMap<int> default_gui_inputs;

    struct Colors {
        static sf::Color button_fill;
        static sf::Color button_outline;
        static sf::Color label_text;

        static float lighting;
    };

    struct Sizes {
        static unsigned int button_outline_thickness;
        static unsigned int layout_spacing;
    };

   private:
    static void initFont();
    static void initEvents();

    static void init();

    static struct __Initiatiser {
        __Initiatiser() { Configuration::init(); };
    } __initiatiser__;
};

}  // namespace gui

}  // namespace foggy

#endif /* GUI_CONFIGURATION_H */
