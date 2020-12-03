Transform = {
    x = -10,
    y = 100
}

CompCollision = {
    body_type = 2,
    fix_angle = true,
    fixture_1 = {
        shape = "Polygon",
        center = {0.5, 0.5},
        vertices = {{-15, 35}, {-15, -35}, {15, -35}, {15, 35}},
        density = 0.5 / (30 * 65),
        friction = 1,
        restitution = 0
    }
}
