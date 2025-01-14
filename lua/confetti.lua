return function(x, y)
    x = x or math.random(0, 1280)
    y = y or 0

    local w, h = 8, 8
    local ox, oy = w/2, h/2
    local rotationRad = math.random() * math.pi / 2
    local hueDeg = math.random(0, 5) * 60
    local red, green, blue = color.FromHSV(hueDeg, 1, 1)

    local body = physics.body();
    body:setPosition(x, y)
    body:setVelocity(0, 4)
    body.Angle = rotationRad
    body.AngularVelocity = math.pi/16
    physics.circleshape(body, oy)

    local spr = sprite.rectangle(x, y, w, h, ox, oy, math.deg(rotationRad), red, green, blue)
    local timer = 0
    local popped
    while spr.nearcamera and not popped do
        coroutine.yield()

        body:UpdateSprite(spr)
        body:EachArbiter(function(arbiter)
            popped = true
        end)

        local mass = body.Mass
        body:setForce(0, -mass/64)

        timer = timer + time.FrameTime

        local sin = math.cos(timer * math.pi * 4)
        local w = (sin + 1) * 4
        spr.width = w
        spr.originX = w/2

        local r, g, b, a = spr:getcolor()
        local sat = (sin + 1) * 128
        if sat > 255 then sat = 255 elseif sat < 1 then sat = 1 end
        if r ~= 0 then r = sat end
        if g ~= 0 then g = sat end
        if b ~= 0 then b = sat end
        spr:setcolor(r, g, b, a)
    end

    body:RemoveFromSpace()
    spr.alpha = 0
    if popped then
        task.run("pop", 0, spr.x, spr.y)
    end
end