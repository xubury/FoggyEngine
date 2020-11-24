#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/ES.hpp"
#include "util/fsm.hpp"
namespace foggy {
namespace component {
template <typename T>
struct Animator : es::Component<T, es::DefaultEntity>, fsmlite::fsm<T> {
   public:
    Animator(int init) : fsmlite::fsm<T>(init) {}
    friend class fsm;

   protected:
    component::Skin::Handle m_anim;
};
}  // namespace component
}  // namespace foggy

#endif /* ANIMATOR_H */
