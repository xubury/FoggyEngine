Transform = {
    x = -10,
    y = 100
}

CompCollision = {
    body_type = 2,
    fix_angle = true,
    fixtures = {
         {
            shape = "Polygon",
            center = {0.5, 0.5},
            vertices = {{x = -15, y = 35}, {x = -15, y = -35}, {x = 15, y = -35}, {x = 15, y = 35}},
            density = 0.5 / (30 /32 * 65 /32),
            friction = 1,
            restitution = 0
        }
    }
}

