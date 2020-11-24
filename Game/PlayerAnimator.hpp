#ifndef PLAYERANIMATOR_H
#define PLAYERANIMATOR_H

#include <iostream>

#include "Configuration/Configuration.hpp"
#include "EntitySystem/Components/Animator.hpp"
#include "EntitySystem/Components/Collision.hpp"
struct PlayerAnimator : foggy::component::Animator<PlayerAnimator> {
   public:
    friend class fsm;
    enum : int { Idle, Squat, Stand, Run, Attack_0, Attack_1, Attack_2 };
    PlayerAnimator();
    struct IdleEvent {};
    struct AttackEvent {
        AttackEvent(bool facing = true) : facing_right(facing) {}
        bool facing_right;
    };
    struct SitEvent {};
    struct StandEvent {};
    struct RunEvent {
        RunEvent(bool facing = true) : facing_right(facing) {}
        bool facing_right;
    };
    PlayerAnimator(const foggy::component::Skin::Handle &handle)
        : Animator(Idle) {
        m_anim = handle;
        m_anim->m_animations.emplace(
            Idle,
            &Configuration::player_anims.Get(Configuration::PlayerAnim::Idle));
        m_anim->m_animations.emplace(Run, &Configuration::player_anims.Get(
                                              Configuration::PlayerAnim::Run));
        m_anim->m_animations.emplace(
            Stand,
            &Configuration::player_anims.Get(Configuration::PlayerAnim::Stand));
        m_anim->m_animations.emplace(
            Squat,
            &Configuration::player_anims.Get(Configuration::PlayerAnim::Suqat));
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

   private:
    void OnIdle(const IdleEvent &) {
        m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Idle));
        m_anim->m_sprite.SetLoop(true);
        m_anim->m_sprite.Play();
    }

    void OnRun(const RunEvent &event) {
        m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Run));
        m_anim->m_sprite.SetLoop(true);
        if (event.facing_right) {
            m_anim->m_sprite.setScale(1, 1);
        } else {
            m_anim->m_sprite.setScale(-1, 1);
        }

        m_anim->m_sprite.Play();
    }

    void OnSquat(const SitEvent &) {
        m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Squat));
        m_anim->m_sprite.SetLoop(false);
        m_anim->m_sprite.SetRepeat(1);
        m_anim->m_sprite.Play();
    }

    void OnStand(const StandEvent &) {
        m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Stand));
        m_anim->m_sprite.SetLoop(false);
        m_anim->m_sprite.SetRepeat(1);
        m_anim->m_sprite.OnFinishd.push_back(
            [this]() { process_event(IdleEvent{}); });
        m_anim->m_sprite.Play();
    }

    void OnFirstAttack(const AttackEvent &event) {
        m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Attack_0));
        m_anim->m_sprite.SetLoop(false);
        m_anim->m_sprite.SetRepeat(1);
        if (event.facing_right) {
            m_anim->m_sprite.setScale(1, 1);
        } else {
            m_anim->m_sprite.setScale(-1, 1);
        }

        m_anim->m_sprite.OnFinishd.push_back(
            [this]() { process_event(IdleEvent{}); });
        m_anim->m_sprite.Play();
    }

    void OnSecondAttack(const AttackEvent &event) {
        m_anim->m_sprite.OnFinishd.pop_back();
        m_anim->m_sprite.OnFinishd.push_back([this]() {
            m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Attack_1));
            m_anim->m_sprite.SetLoop(false);
            m_anim->m_sprite.SetRepeat(1);
            m_anim->m_sprite.Play();
        });
        if (event.facing_right) {
            m_anim->m_sprite.setScale(1, 1);
        } else {
            m_anim->m_sprite.setScale(-1, 1);
        }
        m_anim->m_sprite.OnFinishd.push_back(
            [this]() { process_event(IdleEvent{}); });
    }

    void OnThirdAttack(const AttackEvent &event) {
        m_anim->m_sprite.OnFinishd.pop_back();
        float impulse_x = foggy::converter::PixelsToMeters(120.f);
        if (event.facing_right) {
            m_anim->m_sprite.setScale(1, 1);
        } else {
            m_anim->m_sprite.setScale(-1, 1);
            impulse_x = -impulse_x;
        }
        m_anim->m_sprite.OnFinishd.push_back([this, impulse_x]() {
            m_anim->m_sprite.SetAnimation(m_anim->m_animations.at(Attack_2));
            m_anim->m_sprite.SetLoop(false);
            m_anim->m_sprite.SetRepeat(1);
            m_anim->m_sprite.Play();
            b2Body *b2body_ref =
                m_manager->GetComponent<foggy::component::Collision>(m_owner_id)
                    ->b2body_ref;
            b2body_ref->ApplyLinearImpulse(b2Vec2(impulse_x, 0),
                                           b2body_ref->GetWorldCenter(), true);
        });
        m_anim->m_sprite.OnFinishd.push_back(
            [this]() { process_event(IdleEvent{}); });
    }

   private:
    using transition_table = table<
        mem_fn_row<Idle, RunEvent, Run, &PlayerAnimator::OnRun>,
        mem_fn_row<Idle, SitEvent, Squat, &PlayerAnimator::OnSquat>,
        mem_fn_row<Idle, AttackEvent, Attack_0, &PlayerAnimator::OnFirstAttack>,

        mem_fn_row<Run, IdleEvent, Idle, &PlayerAnimator::OnIdle>,
        mem_fn_row<Run, AttackEvent, Attack_0, &PlayerAnimator::OnFirstAttack>,
        mem_fn_row<Run, SitEvent, Squat, &PlayerAnimator::OnSquat>,

        mem_fn_row<Stand, RunEvent, Run, &PlayerAnimator::OnRun>,
        mem_fn_row<Stand, IdleEvent, Idle, &PlayerAnimator::OnIdle>,

        mem_fn_row<Squat, StandEvent, Stand, &PlayerAnimator::OnStand>,
        mem_fn_row<Squat, AttackEvent, Attack_0,
                   &PlayerAnimator::OnFirstAttack>,

        mem_fn_row<Attack_0, AttackEvent, Attack_1,
                   &PlayerAnimator::OnSecondAttack>,
        mem_fn_row<Attack_0, IdleEvent, Idle, &PlayerAnimator::OnIdle>,

        mem_fn_row<Attack_1, AttackEvent, Attack_2,
                   &PlayerAnimator::OnThirdAttack>,
        mem_fn_row<Attack_1, IdleEvent, Idle, &PlayerAnimator::OnIdle>,

        mem_fn_row<Attack_2, IdleEvent, Idle, &PlayerAnimator::OnIdle> >;
};

#endif /* PLAYERANIMATOR_H */
