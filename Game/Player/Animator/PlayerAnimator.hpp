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
    PlayerAnimator(const foggy::component::Skin::Handle &handle);

   private:
    void OnIdle(const IdleEvent &);
    void OnRun(const RunEvent &event);
    void OnSquat(const SitEvent &);
    void OnStand(const StandEvent &);
    void OnFirstAttack(const AttackEvent &);
    void OnSecondAttack(const AttackEvent &);
    void OnThirdAttack(const AttackEvent &event);

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
