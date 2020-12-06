local machine = require 'res/scripts/statemachine'

CompAnimation = {
    anim_table = machine.create({
        initial = 'idle',
        events = {
            { name = 'Move',  from = 'idle',  to = 'run' },
            { name = 'Reset',  from = 'run',  to = 'idle' },
        },
        callbacks = {
            onMove = function(self, event, from, to)
                print("moving")
            end,
            onReset = function(self, event, from, to)
                print("idle")
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

