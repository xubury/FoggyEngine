require 'res/scripts/Resources'

SwordsmanAnim = enum {
    "Idle"          ,
    "Run"           ,
    "Squat"         ,
    "Sword_Attack_1",
    "Sword_Attack_2",
    "Sword_Attack_3"
}

Animation = {
    swordsman = {
        idle = {
            id = SwordsmanAnim.Idle,
            texture = {Textures.Swordsman_idle_0,
                       Textures.Swordsman_idle_1,
                       Textures.Swordsman_idle_2},
        },
        run = {
            id = SwordsmanAnim.Run,
            texture = {Textures.Swordsman_run_0,
                       Textures.Swordsman_run_1,
                       Textures.Swordsman_run_2,
                       Textures.Swordsman_run_3,
                       Textures.Swordsman_run_4,
                       Textures.Swordsman_run_5, }
        },
        squat = {
            id = SwordsmanAnim.Squat,
            texture = {Textures.Swordsman_crouch_0,
                       Textures.Swordsman_crouch_1,
                       Textures.Swordsman_crouch_2,
                       Textures.Swordsman_crouch_3,}
        },
        attack1 = {
            id = SwordsmanAnim.Sword_Attack_1,
            texture = {Textures.Swordsman_attack1_0,
                       Textures.Swordsman_attack1_1,
                       Textures.Swordsman_attack1_2,
                       Textures.Swordsman_attack1_3,}
        },
        attack2 = {
            id = SwordsmanAnim.Sword_Attack_2,
            texture = {Textures.Swordsman_attack2_0,
                       Textures.Swordsman_attack2_1,
                       Textures.Swordsman_attack2_2,
                       Textures.Swordsman_attack2_3,
                       Textures.Swordsman_attack2_4,
                       Textures.Swordsman_attack2_5, }
        },
        attack3 = {
            id = SwordsmanAnim.Sword_Attack_3,
            texture = {Textures.Swordsman_attack3_0,
                       Textures.Swordsman_attack3_1,
                       Textures.Swordsman_attack3_2,
                       Textures.Swordsman_attack3_3,
                       Textures.Swordsman_attack3_4,
                       Textures.Swordsman_attack3_5, }
        },
    }
}

function loadAnimation(t)
    for i = 1, #t.texture do
        C_loadAnimation(t.id, t.texture[i])
    end
end

function initAnimation()
    loadAnimation(Animation.swordsman.idle)
    loadAnimation(Animation.swordsman.run)
    loadAnimation(Animation.swordsman.squat)
    loadAnimation(Animation.swordsman.attack1)
    loadAnimation(Animation.swordsman.attack2)
    loadAnimation(Animation.swordsman.attack3)
end