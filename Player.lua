Transform = {
    x = -10,
    y = 100
}

local PixelsToMeters = function (x)
    return x / 32
end

CompCollision = {
    body_type = 2,
    fix_angle = true;
    main = {
        shape = "Polygon",
        width = 30,
        height = 65,
        density = 0.5 / (PixelsToMeters(30) * PixelsToMeters(65)) ,
        friction = 1,
        restitution = 0
    }
}
