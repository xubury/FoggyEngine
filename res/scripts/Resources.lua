PlayerAnim = {
    Idle           = 0,
    Run            = 1,
    Stand          = 2,
    Squat          = 3,
    Sword_Attack_0 = 4,
    Sword_Attack_1 = 5,
    Sword_Attack_2 = 6
}

Textures = {
    PlayerAnim_Sheet = 0
}

FontType = {
    GUI = 0,
    Fira = 1
}

Animation = {
    player = {
        idle = {
            id = PlayerAnim.Idle,
            texture = Textures.PlayerAnim_Sheet,
            start_frame = 0,
            end_frame = 3,
            cols = 7,
            rows = 16
        },
        --TODO
        stand = {
            id = PlayerAnim.Stand,
            texture = Textures.PlayerAnim_Sheet,
            start_frame = 0,
            end_frame = 0,
            cols = 7,
            rows = 16
        },
        squat = {
            id = PlayerAnim.Squat,
            texture = Textures.PlayerAnim_Sheet,
            start_frame = 4,
            end_frame = 7,
            cols = 7,
            rows = 16

        },
        run = {
            id = PlayerAnim.Run,
            texture = Textures.PlayerAnim_Sheet,
            start_frame = 8,
            end_frame = 13,
            cols = 7,
            rows = 16

        },
        attack_0 = {
            id = PlayerAnim.Sword_Attack_0,
            texture = Textures.PlayerAnim_Sheet,
            start_frame = 42,
            end_frame = 48,
            cols = 7,
            rows = 16

        },
        attack_1 = {
            id = PlayerAnim.Sword_Attack_1,
            texture = Textures.PlayerAnim_Sheet,
            start_frame = 49,
            end_frame = 52,
            cols = 7,
            rows = 16

        },
        attack_2 = {
            id = PlayerAnim.Sword_Attack_2,
            texture = Textures.PlayerAnim_Sheet,
            start_frame = 53,
            end_frame = 58,
            cols = 7,
            rows = 16

        }
    }
}

function LoadAnimation(t)
    C_loadAnimation(t.id, t.texture, t.start_frame, t.end_frame, t.cols, t.rows)
end

function LoadResources()
    C_loadTexture(Textures.PlayerAnim_Sheet, "res/player/adventurer-v1.5-Sheet.png");
    C_loadFont(FontType.GUI, "res/font/arial.ttf");
    C_loadFont(FontType.Fira, "res/font/fira.ttf");

    LoadAnimation(Animation.player.idle)
    LoadAnimation(Animation.player.run)
    LoadAnimation(Animation.player.squat)
    LoadAnimation(Animation.player.stand)
    LoadAnimation(Animation.player.attack_0)
    LoadAnimation(Animation.player.attack_1)
    LoadAnimation(Animation.player.attack_2)
end

