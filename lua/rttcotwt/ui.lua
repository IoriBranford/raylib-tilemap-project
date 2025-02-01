function draw_life(life)
    pal()
    fillp()
    local y = 121
    local x = 0
    for i = 1, life do
        spr(sprs.heart, x, y)
        x = x + 8
    end
end

function draw_clock()
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
    print("" .. m .. ":" .. s .. ":" .. f, 100, 123, 7)
end