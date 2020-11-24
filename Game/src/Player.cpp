#include <iostream>

#include "Configuration/Configuration.hpp"
#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Components/Transform.hpp"
#include "Player.hpp"
#include "util/converter.hpp"

const sf::Time Player::MIN_TIME_BETWEEN_MOVEMENT = sf::milliseconds(10);

Player::Player(foggy::es::EntityManager<DefaultEntity> *manager, uint32_t id)
    : foggy::es::DefaultEntity(manager, id) {
    foggy::component::Skin::Handle skin =
        manager->AddComponent<foggy::component::Skin>(id);
    skin->m_animations.emplace(
        Anim::Stand,
        &Configuration::player_anims.Get(Configuration::PlayerAnim::Stand));
    skin->m_animations.emplace(Anim::Run, &Configuration::player_anims.Get(
                                              Configuration::PlayerAnim::Run));
}

void Player::Move(const sf::Vector2f &impulse) {
    /* Limit the movement frequncy. Otherwise, the FPS will have huge effect on
     * player movement */
    if (m_movement_timer.getElapsedTime() < MIN_TIME_BETWEEN_MOVEMENT) {
        return;
    }
    b2Body *b2body_ref = Component<foggy::component::Collision>()->b2body_ref;
    b2body_ref->ApplyLinearImpulse(
        b2Vec2(foggy::converter::PixelsToMeters<float>(impulse.x),
               foggy::converter::PixelsToMeters<float>(impulse.y)),
        b2body_ref->GetWorldCenter(), true);
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
        if (collision->debug) {
            for (const auto &shape : collision->debug_shape)
                target.draw(*shape, states);
        }
    }
    if (Has<foggy::component::Skin>()) {
        foggy::component::Skin::Handle skin =
            Component<foggy::component::Skin>();
        if (speed.x > foggy::converter::PixelsToMeters(80.0f)) {
            skin->m_sprite.SetAnimation(skin->m_animations.at(Anim::Run));
            skin->m_sprite.setScale(sf::Vector2f(1, 1));
        } else if (speed.x < foggy::converter::PixelsToMeters(-80.0f)) {
            skin->m_sprite.SetAnimation(skin->m_animations.at(Anim::Run));
            skin->m_sprite.setScale(sf::Vector2f(-1, 1));
        } else {
            skin->m_sprite.SetAnimation(skin->m_animations.at(Anim::Stand));
        }
        target.draw(skin->m_sprite, states);
    }
}
