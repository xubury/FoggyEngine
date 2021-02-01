require 'res/scripts/Resources'

local CharAnimTable = enum {
    "Swordsman_Idle",
    "Swordsman_Run",
    "Swordsman_Squat",
    "Swordsman_Attack_1",
    "Swordsman_Attack_2",
    "Swordsman_Attack_3",
    "ElfMale_Idle",
    "ElfMale_Run"
}

CharAnimation = {}

CharAnimation.ElfMale = {
    idle = {
        id = CharAnimTable.ElfMale_Idle,
        frames = {
            Textures.Elf_Male_Idle_0,
            Textures.Elf_Male_Idle_1,
            Textures.Elf_Male_Idle_2,
            Textures.Elf_Male_Idle_3,
        }
    },
    run = {
        id = CharAnimTable.ElfMale_Run,
        frames = {
            Textures.Elf_Male_Run_0,
            Textures.Elf_Male_Run_1,
            Textures.Elf_Male_Run_2,
            Textures.Elf_Male_Run_3,
        }
    }
}

CharAnimation.Swordsman = {
    idle = {
        id = CharAnimTable.Swordsman_Idle,
        frames = {Textures.Swordsman_idle_0,
                  Textures.Swordsman_idle_1,
                  Textures.Swordsman_idle_2
        },
    },
    run = {
        id = CharAnimTable.Swordsman_Run,
        frames = {Textures.Swordsman_run_0,
                  Textures.Swordsman_run_1,
                  Textures.Swordsman_run_2,
                  Textures.Swordsman_run_3,
                  Textures.Swordsman_run_4,
                  Textures.Swordsman_run_5,
        }
    },
    squat = {
        id = CharAnimTable.Swordsman_Squat,
        frames = {Textures.Swordsman_crouch_0,
                  Textures.Swordsman_crouch_1,
                  Textures.Swordsman_crouch_2,
                  Textures.Swordsman_crouch_3,
        }
    },
    attack1 = {
        id = CharAnimTable.Swordsman_Attack_1,
        frames = {Textures.Swordsman_attack1_0,
                  Textures.Swordsman_attack1_1,
                  Textures.Swordsman_attack1_2,
                  Textures.Swordsman_attack1_3,
        }
    },
    attack2 = {
        id = CharAnimTable.Swordsman_Attack_2,
        frames = {Textures.Swordsman_attack2_0,
                  Textures.Swordsman_attack2_1,
                  Textures.Swordsman_attack2_2,
                  Textures.Swordsman_attack2_3,
                  Textures.Swordsman_attack2_4,
                  Textures.Swordsman_attack2_5,
        }
    },
    attack3 = {
        id = CharAnimTable.Swordsman_Attack_3,
        frames = {Textures.Swordsman_attack3_0,
                  Textures.Swordsman_attack3_1,
                  Textures.Swordsman_attack3_2,
                  Textures.Swordsman_attack3_3,
                  Textures.Swordsman_attack3_4,
                  Textures.Swordsman_attack3_5,
        }
    }
}

function loadCharacterAnimation(t)
    for k,v in pairs(t) do
        for i = 1, #v.frames do
            C_loadCharacterAnimation(v.id, v.frames[i])
        end
    end
end

function initAnimation()
    loadCharacterAnimation(CharAnimation.Swordsman)
    loadCharacterAnimation(CharAnimation.ElfMale)
end