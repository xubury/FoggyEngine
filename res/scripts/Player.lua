local machine = require 'res/scripts/statemachine'
require 'res/scripts/Resources'

CompAnimation = {
    states = machine.create({
        initial = 'idle',
        events = {
            {name = 'Move',   from = 'idle',                                            to = 'run'},
            {name = 'Squat',  from = {'idle', 'run'},                                   to = 'squat'},
            {name = 'Attack', from = {'idle', 'run'},                                   to = 'attack0'},
            {name = 'Attack', from = 'attack0',                                         to = 'attack1'},
            {name = 'Attack', from = 'attack1',                                         to = 'attack2'},
            {name = 'Reset',  from = {'run', 'squat', 'attack0', 'attack1', 'attack2'}, to = 'idle'},
        },
        callbacks = {
            onMove = function(self, event, from, to)
                C_SetAnimation(PlayerAnim.Run)
                C_SetLoop(true)
                C_Play()
            end,
            onReset = function(self, event, from, to)
                C_SetAnimation(PlayerAnim.Idle)
                C_SetLoop(true)
                C_Play()
            end,
            onAttack = function(self, event, from, to)
                print(to)
                if to == 'attack0' then
                    C_SetAnimation(PlayerAnim.Sword_Attack_0)
                elseif to == 'attack1' then
                    C_SetAnimation(PlayerAnim.Sword_Attack_1)
                elseif to == 'attack2' then
                    C_SetAnimation(PlayerAnim.Sword_Attack_2)
                end
                C_SetRepeat(1)
                C_SetLoop(false)
                C_Play()
                C_OnAnimFinish(function ()
                    CompAnimation.states:Reset()
                end);
            end,
            onSquat = function (self, event, from, to)
                C_SetAnimation(PlayerAnim.Squat)
                C_SetLoop(true)
                C_Play()
            end
        }
    })
}

CompCollision = {
    body_type = 2,
    fix_angle = true,
    fixtures = {
        body = {
            shape = "Polygon",
            center = {0.5, 0.5},
            vertices = {{x = -15, y = 35}, {x = -15, y = -35}, {x = 15, y = -35}, {x = 15, y = 35}},
            density = 0.5 / (30 /32 * 65 /32),
            friction = 1,
            restitution = 0
        }
    }
}

function Update()
    local x, y = C_GetSpeed()
    if CompAnimation.states.current == 'run' and math.sqrt(x * x + y * y) < 80 / 32 then
        CompAnimation.states:Reset()
    end
end

local last_move_timer = os.clock()
function Move (x, y)
    local move_timer = os.clock()
    if move_timer - last_move_timer < 1e-2 then
        return
    end
    last_move_timer = move_timer
    C_ApplyLinearImpulse(x, y)
    CompAnimation.states:Move()
end


local last_attack_timer = os.clock()
function Attack()
    local attack_timer = os.clock()
    if attack_timer - last_attack_timer < 0.5 then
        return
    end
    last_attack_timer = attack_timer
    CompAnimation.states:Attack()
end

function Squat()
    CompAnimation.states:Squat()
end

function Stand()
    CompAnimation.states:Reset()    
end
