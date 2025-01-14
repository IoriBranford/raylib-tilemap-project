return function(x, y)
    local w, h = 16, 16
    local ox, oy = w/2, h/2
    local rotationRad = math.random() * math.pi
    local spr = sprite.rectangle(x, y, w, h, ox, oy, math.deg(rotationRad))

    while spr.alpha > 0 do
        coroutine.yield()

        local dt = time.FrameTime
        spr.alpha = spr.alpha - dt*1024
        spr.rotationDeg = spr.rotationDeg + dt*720
        spr.width = spr.width + dt*128
        spr.height = spr.height + dt*128
        spr:setorigin(spr.width/2, spr.height/2)
    end
end