local w, h = 0, 8
local ox, oy = w/2, h/2
local x = math.random(ox, GetScreenWidth()-ox)
local y = 0
local rotationDeg = math.random() * math.pi / 2
local hueDeg = math.random(0, 5) * 60
local color = ColorFromHSV(hueDeg, 1, 1)

local body = Body(x, y, rotationDeg);
body:SetVelocity(0, 4)
body:SetAngularVelocity(math.pi/16)
body:AddCircle(0, 0, ox)

local sprite = RectangleSprite(x, y, w, h, ox, oy, rotationDeg, color)

while true do
    coroutine.yield()

    body:UpdateSprite(sprite)
    if not sprite:IsOnScreen() then
        break
    end

    local mass = body.mass
    body:SetForce(0, -mass/64)

    local spriteAnimTimer = sprite:AdvanceAnimTimer()

    local sin = math.sin(spriteAnimTimer * math.pi / 4)
    local w = (sin + 1) * 4
    sprite.width = w
    sprite.originX = w/2

    local r, g, b, a = sprite:GetColor()
    local sat = (sin + 1) * 128
    if sat > 255 then sat = 255 elseif sat < 1 then sat = 1 end
    if r ~= 0 then r = sat end
    if g ~= 0 then g = sat end
    if b ~= 0 then b = sat end
    sprite:SetColor(r, g, b, a)
end

body:Destroy()
sprite:Release()