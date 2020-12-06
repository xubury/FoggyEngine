#include "Player/Animator/PlayerAnimator.hpp"

PlayerAnimator::PlayerAnimator(const foggy::component::Skin::Handle &handle)
    : Animator(Idle) {
    m_anim = handle;
    m_anim->m_animations.emplace(Idle, &Configuration::player_anims.Get(
                                           Configuration::PlayerAnim::Idle));
    m_anim->m_animations.emplace(
        Run, &Configuration::player_anims.Get(Configuration::PlayerAnim::Run));
    m_anim->m_animations.emplace(Stand, &Configuration::player_anims.Get(
                                            Configuration::PlayerAnim::Stand));
    m_anim->m_animations.emplace(Squat, &Configuration::player_anims.Get(
                                            Configuration::PlayerAnim::Squat));
    m_anim->m_animations.emplace(
        Attack_0, &Configuration::player_anims.Get(
                      Configuration::PlayerAnim::Swoard_Attack_0));
    m_anim->m_animations.emplace(
        Attack_1, &Configuration::player_anims.Get(
                      Configuration::PlayerAnim::Swoard_Attack_1));
    m_anim->m_animations.emplace(
        Attack_2, &Configuration::player_anims.Get(
                      Configuration::PlayerAnim::Swoard_Attack_2));
    m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Idle));
}

void PlayerAnimator::OnIdle(const IdleEvent &) {
    m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Idle));
    m_anim->m_sprite.SetLoop(true);
    m_anim->m_sprite.Play();
}

void PlayerAnimator::OnRun(const RunEvent &event) {
    m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Run));
    m_anim->m_sprite.SetLoop(true);
    if (event.facing_right) {
        m_anim->m_sprite.setScale(1, 1);
    } else {
        m_anim->m_sprite.setScale(-1, 1);
    }

    m_anim->m_sprite.Play();
}

void PlayerAnimator::OnSquat(const SitEvent &) {
    m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Squat));
    m_anim->m_sprite.SetLoop(true);
    m_anim->m_sprite.Play();
}

void PlayerAnimator::OnStand(const StandEvent &) {
    m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Stand));
    m_anim->m_sprite.SetLoop(false);
    m_anim->m_sprite.SetRepeat(1);
    m_anim->m_sprite.OnFinishd.emplace(
        [this]() { process_event(IdleEvent{}); });
    m_anim->m_sprite.Play();
}

void PlayerAnimator::OnFirstAttack(const AttackEvent &) {
    m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Attack_0));
    m_anim->m_sprite.SetLoop(false);
    m_anim->m_sprite.SetRepeat(1);
    m_anim->m_sprite.OnFinishd.emplace(
        [this]() { process_event(IdleEvent{}); });
    m_anim->m_sprite.Play();
}

void PlayerAnimator::OnSecondAttack(const AttackEvent &) {
    m_anim->m_sprite.OnFinishd.emplace([this]() {
        m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Attack_1));
        m_anim->m_sprite.Play();
    });
}

void PlayerAnimator::OnThirdAttack(const AttackEvent &event) {
    float impulse_x = foggy::converter::PixelsToMeters(120.f);
    if (event.facing_right) {
        m_anim->m_sprite.setScale(1, 1);
    } else {
        m_anim->m_sprite.setScale(-1, 1);
        impulse_x = -impulse_x;
    }
    m_anim->m_sprite.OnFinishd.emplace([this, impulse_x]() {
        m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Attack_2));
        m_anim->m_sprite.Play();
        b2Body *b2body_ref =
            Manager()->GetComponent<foggy::component::Collision>(OwnerID())
                ->b2body_ref;
        b2body_ref->ApplyLinearImpulse(b2Vec2(impulse_x, 0),
                                       b2body_ref->GetWorldCenter(), true);
    });
}
