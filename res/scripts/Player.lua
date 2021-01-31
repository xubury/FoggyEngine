local machine = require 'res/scripts/libs/statemachine'
local deque = require 'res/scripts/libs/deque'
require 'res/scripts/Animation'

Animation =  {
    Idle = Swordsman.idle.id,
    Run = Swordsman.run.id,
    Squat = Swordsman.squat.id,
    Sword_Attack_1 = Swordsman.attack1.id,
    Sword_Attack_2 = Swordsman.attack2.id,
    Sword_Attack_3 = Swordsman.attack3.id,
}

local PlayAttackAnim = function (id)
    C_setAnimation(id)
    C_setRepeat(1)
    C_setLoop(false)
    C_play()
end

local front_x = 1

CompAnimation = {
    anim_queue = deque.new(),
    onFinished = function ()
        local q = CompAnimation.anim_queue:peek_left()
        q()
        CompAnimation.anim_queue:pop_left()
    end,
    states = machine.create({
        initial = 'idle',
        events = {
            {name = 'Move',   from = 'idle',                                            to = 'run'},
            {name = 'Squat',  from = {'idle', 'run'},                                   to = 'squat'},
            {name = 'Attack', from = {'idle', 'run'},                                   to = 'attack1'},
            {name = 'Attack', from = 'attack1',                                         to = 'attack2'},
            {name = 'Attack', from = 'attack2',                                         to = 'attack3'},
            {name = 'Reset',  from = {'run', 'squat', 'attack1', 'attack2', 'attack3'}, to = 'idle'},
        },
        callbacks = {
            onMove = function(self, event, from, to)
                C_setAnimation(Animation.Run)
                C_setLoop(true)
                C_play()
            end,
            onReset = function(self, event, from, to)
                C_setAnimation(Animation.Idle)
                C_setLoop(true)
                C_play()
            end,
            onAttack = function(self, event, from, to)
                if to == 'attack1' then
                    PlayAttackAnim(Animation.Sword_Attack_1)
                    CompAnimation.anim_queue:push_right(function ()
                        CompAnimation.states:Reset()
                    end)
                elseif to == 'attack2' then
                    CompAnimation.anim_queue:push_left(function ()
                        PlayAttackAnim(Animation.Sword_Attack_2)
                    end)
                elseif to == 'attack3' then
                    CompAnimation.anim_queue:pop_right()
                    CompAnimation.anim_queue:push_right(function ()
                        C_applyLinearImpulse(100 * front_x, 0)
                        PlayAttackAnim(Animation.Sword_Attack_3)
                    end)
                    CompAnimation.anim_queue:push_right(function ()
                        CompAnimation.states:Reset()
                    end)
                end
            end,
            onSquat = function (self, event, from, to)
                C_setAnimation(Animation.Squat)
                C_setLoop(true)
                C_play()
            end
        }
    })
}

CompCollision = {
    body_type = 2,
    fix_angle = true,
    linear_damping = 10,
    fixtures = {
        body = {
            shape = "Polygon",
            center = {0.5, 0.5},
            vertices = {{x = -7.5, y = 17.5}, {x = -7.5, y = -17.5}, {x = 7.5, y = -17.5}, {x = 7.5, y = 17.5}},
            density = 0.5 / (15 /32 * 32.5 /32),
            friction = 1,
            restitution = 0
        }
    }
}

function update()
    local x, y = C_getSpeed()
    local current = CompAnimation.states.current
    if current == 'run' and math.sqrt(x * x + y * y) < 50 / 32 then
        CompAnimation.states:Reset()
    end
end

local last_move_timer = os.clock()
function move(x, y)
    local current_state = CompAnimation.states.current
    if isAttacking() then
        return
    end
    local move_timer = os.clock()
    if move_timer - last_move_timer < 0.02 then
        return
    end
    if x > 0 then
        front_x = 1
    else
        front_x = -1
    end
    C_setSpriteScale(front_x, 1)
    last_move_timer = move_timer
    if current_state == 'idle' or current_state == 'run' then
        C_applyLinearImpulse(x, y)
    end
    CompAnimation.states:Move()
end


local last_attack_timer = os.clock()
function attack()
    local attack_timer = os.clock()
    if attack_timer - last_attack_timer < 0.2 then
        return
    end
    last_attack_timer = attack_timer
    CompAnimation.states:Attack()
end

function squat()
    CompAnimation.states:Squat()
end

function stand()
    CompAnimation.states:Reset()
end

function isAttacking()
    if string.match(CompAnimation.states.current, "attack%d") then
        return true
    else
        return false
    end
end
