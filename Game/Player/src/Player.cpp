#include <iostream>

#include "Configuration/Configuration.hpp"
#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Components/Controller.hpp"
#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Components/Transform.hpp"
#include "Lua/Handler.hpp"
#include "Player/Animator/PlayerAnimator.hpp"
#include "Player/Player.hpp"
#include "util/converter.hpp"

const sf::Time Player::MIN_TIME_BETWEEN_MOVEMENT = sf::milliseconds(10);
const sf::Time Player::MIN_TIME_BETWEEN_ATTACK = sf::seconds(0.5);

Player::Player(foggy::es::EntityManager<DefaultEntity> *manager, uint32_t id)
    : foggy::es::DefaultEntity(manager, id), m_facing_right(true) {
    float scale = 2;
    Component<foggy::component::Transform>()->setScale(scale, scale);
    foggy::component::Skin::Handle skin =
        manager->AddComponent<foggy::component::Skin>(id);

    manager->AddComponent<PlayerAnimator>(id, skin);

    foggy::LuaManager &lua_manager = foggy::LuaManager::Instance();
    lua_manager.Lua<foggy::es::LuaCollision>()->InitComponent(manager, id,
                                                              "../Player.lua");

    foggy::component::Controller::Handle handle =
        manager->AddComponent<foggy::component::Controller>(
            id, Configuration::player_inputs);
    handle->Bind(Configuration::PlayerInput::Up,
                 [this](const sf::Event &) { Move(sf::Vector2f(0, 20)); });
    handle->Bind(Configuration::PlayerInput::Down,
                 [this](const sf::Event &) { Squat(); });
    handle->Bind(Configuration::PlayerInput::Down_Realeased,
                 [this](const sf::Event &) { Standup(); });
    handle->Bind(Configuration::PlayerInput::Left,
                 [this](const sf::Event &) { Move(sf::Vector2f(-10, 0)); });
    handle->Bind(Configuration::PlayerInput::Right,
                 [this](const sf::Event &) { Move(sf::Vector2f(10, 0)); });
    handle->Bind(Configuration::PlayerInput::Attack,
                 [this](const sf::Event &) { Attack(); });
}

void Player::Move(const sf::Vector2f &impulse) {
    /* Limit the movement frequncy. Otherwise, the FPS will have huge effect on
     * player movement */
    if (m_movement_timer.getElapsedTime() < MIN_TIME_BETWEEN_MOVEMENT) {
        return;
    }
    PlayerAnimator::Handle animator = Component<PlayerAnimator>();
    int state = animator->current_state();
    if (state != PlayerAnimator::Idle && state != PlayerAnimator::Run) return;

    b2Body *b2body_ref = Component<foggy::component::Collision>()->b2body_ref;
    b2body_ref->ApplyLinearImpulse(
        b2Vec2(foggy::converter::PixelsToMeters<float>(impulse.x),
               foggy::converter::PixelsToMeters<float>(impulse.y)),
        b2body_ref->GetWorldCenter(), true);
    if (impulse.x > 0) {
        m_facing_right = true;
        animator->process_event(PlayerAnimator::RunEvent(m_facing_right));
    } else if (impulse.x < 0) {
        m_facing_right = false;
        animator->process_event(PlayerAnimator::RunEvent(m_facing_right));
    }
    m_movement_timer.restart();
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    const sf::Transform &trans =
        Component<foggy::component::Transform>()->getTransform();
    states.transform = trans;
    b2Vec2 speed;
    if (Has<foggy::component::Collision>()) {
        foggy::component::Collision::Handle collision =
            Component<foggy::component::Collision>();
        speed = collision->b2body_ref->GetLinearVelocity();
    }
    if (Has<foggy::component::Skin>()) {
        foggy::component::Skin::Handle skin =
            Component<foggy::component::Skin>();
        PlayerAnimator::Handle animator = Component<PlayerAnimator>();
        if (animator->current_state() == PlayerAnimator::Run &&
            abs(speed.x) < foggy::converter::PixelsToMeters(80.0f)) {
            animator->process_event(PlayerAnimator::IdleEvent());
        }
        target.draw(skin->m_sprite, states);
    }
    DefaultEntity::draw(target, states);
}

void Player::Attack() {
    if (m_attack_timer.getElapsedTime() < MIN_TIME_BETWEEN_ATTACK) {
        return;
    }
    Component<PlayerAnimator>()->process_event(
        PlayerAnimator::AttackEvent(m_facing_right));
    m_attack_timer.restart();
}

void Player::Squat() {
    Component<PlayerAnimator>()->process_event(PlayerAnimator::SitEvent());
}

void Player::Standup() {
    Component<PlayerAnimator>()->process_event(PlayerAnimator::StandEvent());
}
