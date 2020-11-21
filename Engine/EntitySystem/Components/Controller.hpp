#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ActionSystem/ActionTarget.hpp"
#include "Configuration/Configuration.hpp"
#include "EntitySystem/Components/Component.hpp"
#include "EntitySystem/Entities/Entity.hpp"

namespace foggy {
namespace component {

struct Controller : es::Component<Controller, es::DefaultEntity>,
                    foggy::ActionTarget<int> {
   public:
    Controller(foggy::ActionMap<int> &map) : foggy::ActionTarget<int>(map) {}
};
}  // namespace component

}  // namespace foggy

#endif /* CONTROLLER_H */
