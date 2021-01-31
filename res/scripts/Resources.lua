require 'res/scripts/libs/enum'
Textures = enum {
    "Swordsman_idle_0",
    "Swordsman_idle_1",
    "Swordsman_idle_2",

    "Swordsman_attack1_0",
    "Swordsman_attack1_1",
    "Swordsman_attack1_2",
    "Swordsman_attack1_3",

    "Swordsman_attack2_0",
    "Swordsman_attack2_1",
    "Swordsman_attack2_2",
    "Swordsman_attack2_3",
    "Swordsman_attack2_4",
    "Swordsman_attack2_5",

    "Swordsman_attack3_0",
    "Swordsman_attack3_1",
    "Swordsman_attack3_2",
    "Swordsman_attack3_3",
    "Swordsman_attack3_4",
    "Swordsman_attack3_5",

    "Swordsman_run_0",
    "Swordsman_run_1",
    "Swordsman_run_2",
    "Swordsman_run_3",
    "Swordsman_run_4",
    "Swordsman_run_5",

    "Swordsman_crouch_0",
    "Swordsman_crouch_1",
    "Swordsman_crouch_2",
    "Swordsman_crouch_3",

    "Elf_Male_Idle_0",
    "Elf_Male_Idle_1",
    "Elf_Male_Idle_2",
    "Elf_Male_Idle_3",

    "Elf_Male_Run_0",
    "Elf_Male_Run_1",
    "Elf_Male_Run_2",
    "Elf_Male_Run_3",
}

Font = enum {
    "GUI",
    "Fira"
}


function loadResources()
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

    C_loadTexture(Textures.Elf_Male_Idle_0, "res/player/elf/elf_m_idle_anim_f0.png");
    C_loadTexture(Textures.Elf_Male_Idle_1, "res/player/elf/elf_m_idle_anim_f1.png");
    C_loadTexture(Textures.Elf_Male_Idle_2, "res/player/elf/elf_m_idle_anim_f2.png");
    C_loadTexture(Textures.Elf_Male_Idle_3, "res/player/elf/elf_m_idle_anim_f3.png");

    C_loadTexture(Textures.Elf_Male_Run_0, "res/player/elf/elf_m_run_anim_f0.png");
    C_loadTexture(Textures.Elf_Male_Run_1, "res/player/elf/elf_m_run_anim_f1.png");
    C_loadTexture(Textures.Elf_Male_Run_2, "res/player/elf/elf_m_run_anim_f2.png");
    C_loadTexture(Textures.Elf_Male_Run_3, "res/player/elf/elf_m_run_anim_f3.png");

    C_loadFont(Font.GUI, "res/font/arial.ttf");
    C_loadFont(Font.Fira, "res/font/fira.ttf");

end
