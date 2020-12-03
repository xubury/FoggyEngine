Transform = {
    x = -10,
    y = 100
}

CompCollision = {
    body_type = 2,
    fix_angle = true,
    fixture_1 = {
        shape = "Polygon",
        width = 30,
        height = 65,
        density = 0.5 / (30 * 65),
        friction = 1,
        restitution = 0
    },
    fixture_2 = {
        shape = "Circle",
        radius = 30,
        density = 0.5 / (30 * 30),
        friction = 1,
        restitution = 0
    }
}
