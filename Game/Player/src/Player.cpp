#include <iostream>

#include "Configuration/Configuration.hpp"
#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Components/Controller.hpp"
#include "EntitySystem/Components/LuaScript.hpp"
#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Components/Transform.hpp"
#include "Player/Player.hpp"

Player::Player(foggy::es::EntityManager<DefaultEntity> *manager, uint32_t id)
    : foggy::es::DefaultEntity(manager, id), m_facing_right(true) {
    float scale = 2;
    component<foggy::component::Transform>()->setScale(scale, scale);

    auto lua_script = manager->AddComponent<foggy::component::LuaScript>(id);
    lua_script->initScript("res/scripts/Player.lua");
    lua_script->lua.set_function(
        "C_ApplyLinearImpulse", [this](float x, float y) {
            b2Body *b2body_ref =
                component<foggy::component::Collision>()->b2body_ref;
            b2body_ref->ApplyLinearImpulse(
                b2Vec2(foggy::converter::pixelsToMeters<float>(x),
                       foggy::converter::pixelsToMeters<float>(y)),
                b2body_ref->GetWorldCenter(), true);
        });

    auto skin = component<foggy::component::Skin>();

    foggy::component::Controller::Handle handle =
        manager->AddComponent<foggy::component::Controller>(
            id, Configuration::player_inputs);
    handle->Bind(
        Configuration::PlayerInput::Up,
        [s = lua_script.get()](const sf::Event &) { s->lua["Move"](0, 20); });
    handle->Bind(
        Configuration::PlayerInput::Down,
        [s = lua_script.get()](const sf::Event &) { s->lua["Squat"](); });
    handle->Bind(
        Configuration::PlayerInput::Down_Realeased,
        [s = lua_script.get()](const sf::Event &) { s->lua["Stand"](); });
    handle->Bind(
        Configuration::PlayerInput::Left,
        [s = lua_script.get()](const sf::Event &) { s->lua["Move"](-10, 0); });
    handle->Bind(
        Configuration::PlayerInput::Right,
        [s = lua_script.get()](const sf::Event &) { s->lua["Move"](10, 0); });
    handle->Bind(
        Configuration::PlayerInput::Attack,
        [s = lua_script.get()](const sf::Event &) { s->lua["Attack"](); });

    skin->m_animations.emplace(
        Configuration::PlayerAnim::Idle,
        &Configuration::player_anims.Get(Configuration::PlayerAnim::Idle));
    skin->m_animations.emplace(
        Configuration::PlayerAnim::Run,
        &Configuration::player_anims.Get(Configuration::PlayerAnim::Run));
    skin->m_animations.emplace(
        Configuration::PlayerAnim::Stand,
        &Configuration::player_anims.Get(Configuration::PlayerAnim::Stand));
    skin->m_animations.emplace(
        Configuration::PlayerAnim::Squat,
        &Configuration::player_anims.Get(Configuration::PlayerAnim::Squat));
    skin->m_animations.emplace(Configuration::PlayerAnim::Sword_Attack_0,
                               &Configuration::player_anims.Get(
                                   Configuration::PlayerAnim::Sword_Attack_0));
    skin->m_animations.emplace(Configuration::PlayerAnim::Sword_Attack_1,
                               &Configuration::player_anims.Get(
                                   Configuration::PlayerAnim::Sword_Attack_1));
    skin->m_animations.emplace(Configuration::PlayerAnim::Sword_Attack_2,
                               &Configuration::player_anims.Get(
                                   Configuration::PlayerAnim::Sword_Attack_2));
    skin->m_sprite.setAnimation(
        skin->m_animations.at(Configuration::PlayerAnim::Idle));
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    const sf::Transform &trans =
        component<foggy::component::Transform>()->getTransform();
    states.transform = trans;
    if (has<foggy::component::Skin>()) {
        foggy::component::Skin::Handle skin =
            component<foggy::component::Skin>();
        target.draw(skin->m_sprite, states);
    }
    DefaultEntity::draw(target, states);
}
