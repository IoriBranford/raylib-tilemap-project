local lifebar = {}
local gameover = nil

local uiz = 100
uicam = sprite.camera()
uicam.z = uiz - 1

uiclock = newtxt("0:00:00", 100, 123)
uiclock.z = uiz

function add_lifebar()
    local y = 121
    local x = 0
    for i = 1, ninmaxstartlife do
        local s = newspr(sprs.heart, x, y)
        s.z = uiz
        add(lifebar, s)
        x = x + 8
    end
end

function add_game_over()
    gameover = newspr(sprs.gameover,
                64 - 16, 64 - 8,
                4, 2)
    gameover.z = uiz
end

function update_lifebar(life)
    for i = 1, life do
        lifebar[i].alpha = 255
    end
    for i = life+1, ninmaxstartlife do
        lifebar[i].alpha = 0
    end
end

function update_clock()
    local f = clock % 60
    local s = flr(clock / 60) % 60
    local m = flr(clock / 3600)
    if f < 10 then
        f = "0" .. f
    end
    if s < 10 then
        s = "0" .. s
    end
    pal()
    fillp()
    sprtxt(uiclock, "" .. m .. ":" .. s .. ":" .. f)
end