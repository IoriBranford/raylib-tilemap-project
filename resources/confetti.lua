return {
    start = function(self)
        local w, h = 0, 8
        local ox, oy = w/2, h/2
        local x = math.random(ox, GetScreenWidth()-ox)
        local y = 0
        local rotationDeg = math.random() * math.pi / 2
        local hueDeg = math.random(0, 5) * 60
        local color = ColorFromHSV(hueDeg, 1, 1)

        local body = NewBody(x, y, rotationDeg);
        self.body = body
        b2Body_SetLinearVelocity(body, 0, 4)
        b2Body_SetAngularVelocity(body, math.pi/16)
        AddBodyCircle(body, 0, 0, ox)

        local sprite = NewRectangleSprite(x, y, w, h, ox, oy, rotationDeg, color)
        self.sprite = sprite
    end,

    update = function(self)
        local body = self.body
        local sprite = self.sprite

        UpdateSpriteFromBody(body, sprite)
        if (!IsSpriteOnScreen(sprite)) then
            b2DestroyBody(body)
            ReleaseSprite(sprite)
            EndTask(self)
            return
        end

        local mass = b2Body_GetMass(body)
        b2Body_ApplyForceToCenter(body, 0, -mass/64, true)

        local spriteAnimTimer = AdvanceSpriteAnimTimer(sprite)

        local sin = math.sin(spriteAnimTimer * math.pi / 4)
        local w = (sin + 1) * 4
        SetSpriteSize(w, 8)
        SetSpriteOrigin(w/2, 4)

        local r, g, b, a = GetSpriteColor(sprite)
        local sat = (sin + 1) * 128
        if sat > 255 then sat = 255 elseif sat < 1 then sat = 1 end
        if r ~= 0 then r = sat end
        if g ~= 0 then g = sat end
        if b ~= 0 then b = sat end
        SetSpriteColor(r, g, b, a)
    end
}