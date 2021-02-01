local machine = require 'res/scripts/libs/statemachine'
local deque = require 'res/scripts/libs/deque'
require 'res/scripts/Animation'

CompAnimation = {
    Animation =  {
        Idle = CharAnimation.ElfMale.idle.id,
        Run = CharAnimation.ElfMale.run.id
    },
    initialize = function ()
        C_setAnimation(CompAnimation.Animation.Idle)
        C_setLoop(true)
        C_play()
    end,
    states = machine.create({
        initial = 'idle',
        events = {
            {name = 'Move',   from = 'idle',to = 'run'},
            {name = 'Reset',  from = 'run', to = 'idle'},
        },
        callbacks = {
            onMove = function(self, event, from, to)
                C_setAnimation(CompAnimation.Animation.Run)
                C_setLoop(true)
                C_play()
            end,
            onReset = function(self, event, from, to)
                C_setAnimation(CompAnimation.Animation.Idle)
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
            vertices = {{x = -7.5, y = 14}, {x = -7.5, y = -6}, {x = 7.5, y = -6}, {x = 7.5, y = 14}},
            density = 0.5 / (15 / 32 * 22 / 32),
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

local front_x = 1
local last_move_timer = os.clock()
function move(x, y)
    local current_state = CompAnimation.states.current
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
