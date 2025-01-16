return function(obj, map)
    local x = x or math.random(0, 1280)
    local y = y or 0

    local width = obj.width
    local rotationRad = math.random() * math.pi / 2
    local hueDeg = math.random(0, 5) * 60
    local red, green, blue = ColorFromHSV(hueDeg, 1, 1)

    local body = obj:new_body(map)
    body:setPosition(x, y)
    body:setVelocity(0, 4)
    body.Angle = rotationRad
    body.AngularVelocity = math.pi/16
    body:NewCircleShape(width/2)

    local spr = obj:new_sprite(map, red, green, blue)
    body:UpdateSprite(spr)

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

        timer = timer + GetFrameTime()

        local sin = math.sin(timer * math.pi * 4)
        local w = (sin + 1) * width / 2
        spr.width = w
        spr.originX = w/2

        local r, g, b, a = spr:getcolor()
        local sat = (sin + 1) * 128
        if sat < 1 then sat = 1 end
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