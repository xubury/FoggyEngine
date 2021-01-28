PlayerAnim = {
    Idle           = 0,
    Run            = 1,
    Squat          = 2,
    Sword_Attack_1 = 3,
    Sword_Attack_2 = 4,
    Sword_Attack_3 = 5
}

Textures = {
    SwordMan_idle_0 = 0,
    SwordMan_idle_1 = 1,
    SwordMan_idle_2 = 2,

    SwordMan_attack1_0 = 3,
    SwordMan_attack1_1 = 4,
    SwordMan_attack1_2 = 5,
    SwordMan_attack1_3 = 6,

    SwordMan_attack2_0 = 7,
    SwordMan_attack2_1 = 8,
    SwordMan_attack2_2 = 9,
    SwordMan_attack2_3 = 10,
    SwordMan_attack2_4 = 11,
    SwordMan_attack2_5 = 12,

    SwordMan_attack3_0 = 13,
    SwordMan_attack3_1 = 14,
    SwordMan_attack3_2 = 15,
    SwordMan_attack3_3 = 16,
    SwordMan_attack3_4 = 17,
    SwordMan_attack3_5 = 18,

    SwordMan_run_0 = 19,
    SwordMan_run_1 = 20,
    SwordMan_run_2 = 21,
    SwordMan_run_3 = 22,
    SwordMan_run_4 = 23,
    SwordMan_run_5 = 24,

    SwordMan_crouch_0 = 25,
    SwordMan_crouch_1 = 26,
    SwordMan_crouch_2 = 27,
    SwordMan_crouch_3 = 28,
}

FontType = {
    GUI = 0,
    Fira = 1
}

Animation = {
    player = {
        idle = {
            id = PlayerAnim.Idle,
            texture = {Textures.SwordMan_idle_0,
                       Textures.SwordMan_idle_1,
                       Textures.SwordMan_idle_2},
        },
        run = {
            id = PlayerAnim.Run,
            texture = {Textures.SwordMan_run_0,
                       Textures.SwordMan_run_1,
                       Textures.SwordMan_run_2,
                       Textures.SwordMan_run_3,
                       Textures.SwordMan_run_4,
                       Textures.SwordMan_run_5, }
        },
        squat = {
            id = PlayerAnim.Squat,
            texture = {Textures.SwordMan_crouch_0,
                       Textures.SwordMan_crouch_1,
                       Textures.SwordMan_crouch_2,
                       Textures.SwordMan_crouch_3,}
        },
        attack1 = {
            id = PlayerAnim.Sword_Attack_1,
            texture = {Textures.SwordMan_attack1_0,
                       Textures.SwordMan_attack1_1,
                       Textures.SwordMan_attack1_2,
                       Textures.SwordMan_attack1_3,}
        },
        attack2 = {
            id = PlayerAnim.Sword_Attack_2,
            texture = {Textures.SwordMan_attack2_0,
                       Textures.SwordMan_attack2_1,
                       Textures.SwordMan_attack2_2,
                       Textures.SwordMan_attack2_3,
                       Textures.SwordMan_attack2_4,
                       Textures.SwordMan_attack2_5, }
        },
        attack3 = {
            id = PlayerAnim.Sword_Attack_3,
            texture = {Textures.SwordMan_attack3_0,
                       Textures.SwordMan_attack3_1,
                       Textures.SwordMan_attack3_2,
                       Textures.SwordMan_attack3_3,
                       Textures.SwordMan_attack3_4,
                       Textures.SwordMan_attack3_5, }
        },
    }
}

function LoadAnimation(t)
    for i = 1, #t.texture do
        C_loadAnimation(t.id, t.texture[i])
    end
end

function LoadResources()
    C_loadTexture(Textures.SwordMan_idle_0, "res/player/Individual Sprites/adventurer-idle-00.png");
    C_loadTexture(Textures.SwordMan_idle_1, "res/player/Individual Sprites/adventurer-idle-01.png");
    C_loadTexture(Textures.SwordMan_idle_2, "res/player/Individual Sprites/adventurer-idle-02.png");

    C_loadTexture(Textures.SwordMan_attack1_0, "res/player/Individual Sprites/adventurer-attack1-00.png");
    C_loadTexture(Textures.SwordMan_attack1_1, "res/player/Individual Sprites/adventurer-attack1-01.png");
    C_loadTexture(Textures.SwordMan_attack1_2, "res/player/Individual Sprites/adventurer-attack1-02.png");
    C_loadTexture(Textures.SwordMan_attack1_3, "res/player/Individual Sprites/adventurer-attack1-03.png");

    C_loadTexture(Textures.SwordMan_attack2_0, "res/player/Individual Sprites/adventurer-attack2-00.png");
    C_loadTexture(Textures.SwordMan_attack2_1, "res/player/Individual Sprites/adventurer-attack2-01.png");
    C_loadTexture(Textures.SwordMan_attack2_2, "res/player/Individual Sprites/adventurer-attack2-02.png");
    C_loadTexture(Textures.SwordMan_attack2_3, "res/player/Individual Sprites/adventurer-attack2-03.png");
    C_loadTexture(Textures.SwordMan_attack2_4, "res/player/Individual Sprites/adventurer-attack2-04.png");
    C_loadTexture(Textures.SwordMan_attack2_5, "res/player/Individual Sprites/adventurer-attack2-05.png");

    C_loadTexture(Textures.SwordMan_attack3_0, "res/player/Individual Sprites/adventurer-attack3-00.png");
    C_loadTexture(Textures.SwordMan_attack3_1, "res/player/Individual Sprites/adventurer-attack3-01.png");
    C_loadTexture(Textures.SwordMan_attack3_2, "res/player/Individual Sprites/adventurer-attack3-02.png");
    C_loadTexture(Textures.SwordMan_attack3_3, "res/player/Individual Sprites/adventurer-attack3-03.png");
    C_loadTexture(Textures.SwordMan_attack3_4, "res/player/Individual Sprites/adventurer-attack3-04.png");
    C_loadTexture(Textures.SwordMan_attack3_5, "res/player/Individual Sprites/adventurer-attack3-05.png");

    C_loadTexture(Textures.SwordMan_run_0, "res/player/Individual Sprites/adventurer-run-00.png");
    C_loadTexture(Textures.SwordMan_run_1, "res/player/Individual Sprites/adventurer-run-01.png");
    C_loadTexture(Textures.SwordMan_run_2, "res/player/Individual Sprites/adventurer-run-02.png");
    C_loadTexture(Textures.SwordMan_run_3, "res/player/Individual Sprites/adventurer-run-03.png");
    C_loadTexture(Textures.SwordMan_run_4, "res/player/Individual Sprites/adventurer-run-04.png");
    C_loadTexture(Textures.SwordMan_run_5, "res/player/Individual Sprites/adventurer-run-05.png");

    C_loadTexture(Textures.SwordMan_crouch_0, "res/player/Individual Sprites/adventurer-crouch-00.png");
    C_loadTexture(Textures.SwordMan_crouch_1, "res/player/Individual Sprites/adventurer-crouch-01.png");
    C_loadTexture(Textures.SwordMan_crouch_2, "res/player/Individual Sprites/adventurer-crouch-02.png");
    C_loadTexture(Textures.SwordMan_crouch_3, "res/player/Individual Sprites/adventurer-crouch-03.png");

    C_loadFont(FontType.GUI, "res/font/arial.ttf");
    C_loadFont(FontType.Fira, "res/font/fira.ttf");

    LoadAnimation(Animation.player.idle)
    LoadAnimation(Animation.player.run)
    LoadAnimation(Animation.player.squat)
    LoadAnimation(Animation.player.attack1)
    LoadAnimation(Animation.player.attack2)
    LoadAnimation(Animation.player.attack3)
end
