#include "Player/Player.hpp"

#include <iostream>

#include "Configuration/Configuration.hpp"
#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Components/Controller.hpp"
#include "EntitySystem/Components/LuaScript.hpp"
#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Components/Transform.hpp"

Player::Player(foggy::es::EntityManager<DefaultEntity> *manager, uint32_t id)
    : foggy::es::DefaultEntity(manager, id), m_facing_right(true) {
    auto lua_script = manager->addComponent<foggy::component::LuaScript>(id);
    lua_script->initScript("res/scripts/Player.lua");
    lua_script->lua.set_function(
        "C_applyLinearImpulse", [this](float x, float y) {
            b2Body *b2body_ref =
                component<foggy::component::Collision>()->b2body_ref;
            b2body_ref->ApplyLinearImpulse(
                b2Vec2(foggy::converter::pixelsToMeters<float>(x),
                       foggy::converter::pixelsToMeters<float>(y)),
                b2body_ref->GetWorldCenter(), true);
        });

    auto skin = component<foggy::component::Skin>();

    foggy::component::Controller::Handle handle =
        manager->addComponent<foggy::component::Controller>(
            id, Configuration::player_inputs);
    handle->bind(
        Configuration::PlayerInput::Up,
        [s = lua_script.get()](const sf::Event &) { s->lua["move"](0, -20); });
    handle->bind(
        Configuration::PlayerInput::Down,
        [s = lua_script.get()](const sf::Event &) { s->lua["move"](0, 20); });
    handle->bind(
        Configuration::PlayerInput::Down_Realeased,
        [s = lua_script.get()](const sf::Event &) { s->lua["stand"](); });
    handle->bind(
        Configuration::PlayerInput::Left,
        [s = lua_script.get()](const sf::Event &) { s->lua["move"](-20, 0); });
    handle->bind(
        Configuration::PlayerInput::Right,
        [s = lua_script.get()](const sf::Event &) { s->lua["move"](20, 0); });
    handle->bind(
        Configuration::PlayerInput::Attack,
        [s = lua_script.get()](const sf::Event &) { s->lua["attack"](); });

    sol::table table =
        foggy::Resource::instance().GetResouceTable("SwordsmanAnim");
    for (const auto &[key, value] : table) {
        skin->m_animations.emplace(
            value.as<int>(), &Configuration::player_anims.get(value.as<int>()));
    }
    int resource_id =
        foggy::Resource::instance().getResourceID("SwordsmanAnim", "Idle");
    skin->m_sprite.setAnimation(skin->m_animations.at(resource_id));
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform.translate(getPosition());
    if (has<foggy::component::Skin>()) {
        foggy::component::Skin::Handle skin =
            component<foggy::component::Skin>();
        target.draw(skin->m_sprite, states);
    }
    DefaultEntity::draw(target, states);
}
