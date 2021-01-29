SwordsmanAnim = {
    Idle           = 0,
    Run            = 1,
    Squat          = 2,
    Sword_Attack_1 = 3,
    Sword_Attack_2 = 4,
    Sword_Attack_3 = 5
}

Textures = {
    Swordsman_idle_0 = 0,
    Swordsman_idle_1 = 1,
    Swordsman_idle_2 = 2,

    Swordsman_attack1_0 = 3,
    Swordsman_attack1_1 = 4,
    Swordsman_attack1_2 = 5,
    Swordsman_attack1_3 = 6,

    Swordsman_attack2_0 = 7,
    Swordsman_attack2_1 = 8,
    Swordsman_attack2_2 = 9,
    Swordsman_attack2_3 = 10,
    Swordsman_attack2_4 = 11,
    Swordsman_attack2_5 = 12,

    Swordsman_attack3_0 = 13,
    Swordsman_attack3_1 = 14,
    Swordsman_attack3_2 = 15,
    Swordsman_attack3_3 = 16,
    Swordsman_attack3_4 = 17,
    Swordsman_attack3_5 = 18,

    Swordsman_run_0 = 19,
    Swordsman_run_1 = 20,
    Swordsman_run_2 = 21,
    Swordsman_run_3 = 22,
    Swordsman_run_4 = 23,
    Swordsman_run_5 = 24,

    Swordsman_crouch_0 = 25,
    Swordsman_crouch_1 = 26,
    Swordsman_crouch_2 = 27,
    Swordsman_crouch_3 = 28,
}

FontType = {
    GUI = 0,
    Fira = 1
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

function LoadAnimation(t)
    for i = 1, #t.texture do
        C_loadAnimation(t.id, t.texture[i])
    end
end

function LoadResources()
    C_loadTexture(Textures.Swordsman_idle_0, "res/player/Individual Sprites/adventurer-idle-00.png");
    C_loadTexture(Textures.Swordsman_idle_1, "res/player/Individual Sprites/adventurer-idle-01.png");
    C_loadTexture(Textures.Swordsman_idle_2, "res/player/Individual Sprites/adventurer-idle-02.png");

    C_loadTexture(Textures.Swordsman_attack1_0, "res/player/Individual Sprites/adventurer-attack1-00.png");
    C_loadTexture(Textures.Swordsman_attack1_1, "res/player/Individual Sprites/adventurer-attack1-01.png");
    C_loadTexture(Textures.Swordsman_attack1_2, "res/player/Individual Sprites/adventurer-attack1-02.png");
    C_loadTexture(Textures.Swordsman_attack1_3, "res/player/Individual Sprites/adventurer-attack1-03.png");

    C_loadTexture(Textures.Swordsman_attack2_0, "res/player/Individual Sprites/adventurer-attack2-00.png");
    C_loadTexture(Textures.Swordsman_attack2_1, "res/player/Individual Sprites/adventurer-attack2-01.png");
    C_loadTexture(Textures.Swordsman_attack2_2, "res/player/Individual Sprites/adventurer-attack2-02.png");
    C_loadTexture(Textures.Swordsman_attack2_3, "res/player/Individual Sprites/adventurer-attack2-03.png");
    C_loadTexture(Textures.Swordsman_attack2_4, "res/player/Individual Sprites/adventurer-attack2-04.png");
    C_loadTexture(Textures.Swordsman_attack2_5, "res/player/Individual Sprites/adventurer-attack2-05.png");

    C_loadTexture(Textures.Swordsman_attack3_0, "res/player/Individual Sprites/adventurer-attack3-00.png");
    C_loadTexture(Textures.Swordsman_attack3_1, "res/player/Individual Sprites/adventurer-attack3-01.png");
    C_loadTexture(Textures.Swordsman_attack3_2, "res/player/Individual Sprites/adventurer-attack3-02.png");
    C_loadTexture(Textures.Swordsman_attack3_3, "res/player/Individual Sprites/adventurer-attack3-03.png");
    C_loadTexture(Textures.Swordsman_attack3_4, "res/player/Individual Sprites/adventurer-attack3-04.png");
    C_loadTexture(Textures.Swordsman_attack3_5, "res/player/Individual Sprites/adventurer-attack3-05.png");

    C_loadTexture(Textures.Swordsman_run_0, "res/player/Individual Sprites/adventurer-run-00.png");
    C_loadTexture(Textures.Swordsman_run_1, "res/player/Individual Sprites/adventurer-run-01.png");
    C_loadTexture(Textures.Swordsman_run_2, "res/player/Individual Sprites/adventurer-run-02.png");
    C_loadTexture(Textures.Swordsman_run_3, "res/player/Individual Sprites/adventurer-run-03.png");
    C_loadTexture(Textures.Swordsman_run_4, "res/player/Individual Sprites/adventurer-run-04.png");
    C_loadTexture(Textures.Swordsman_run_5, "res/player/Individual Sprites/adventurer-run-05.png");

    C_loadTexture(Textures.Swordsman_crouch_0, "res/player/Individual Sprites/adventurer-crouch-00.png");
    C_loadTexture(Textures.Swordsman_crouch_1, "res/player/Individual Sprites/adventurer-crouch-01.png");
    C_loadTexture(Textures.Swordsman_crouch_2, "res/player/Individual Sprites/adventurer-crouch-02.png");
    C_loadTexture(Textures.Swordsman_crouch_3, "res/player/Individual Sprites/adventurer-crouch-03.png");

    C_loadFont(FontType.Fira, "res/font/fira.ttf");

    LoadAnimation(Animation.swordsman.idle)
    LoadAnimation(Animation.swordsman.run)
    LoadAnimation(Animation.swordsman.squat)
    LoadAnimation(Animation.swordsman.attack1)
    LoadAnimation(Animation.swordsman.attack2)
    LoadAnimation(Animation.swordsman.attack3)
end
