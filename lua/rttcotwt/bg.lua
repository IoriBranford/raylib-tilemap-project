local STARZ = -20
local stars = {}

for y = 16, 80, 32 do
    for x = 16, 80, 32 do
        local s = sprite.rectangle(
            x + rnd(32), y + rnd(32),
            1, 1,
            0, 0,
            0, 0xFFFFFFFF)
        s.z = STARZ
        add(stars, s)
    end
end

-- local clouds = {}
-- for y = 120, 128, 8 do
--     for x = 0, 112, 16 do
--         add(clouds, x + rnd(16))
--         add(clouds, y + rnd(16))
--     end
-- end

-- function draw_sky()
--     pal()
--     fillp("░")
--     rectfill(0, 104, 128, 108, 1)
--     fillp("▒")
--     rectfill(0, 108, 128, 128, 1)
--     fillp()
--     circfill(96, 24, 4, 6)
--     for i = 2, #stars, 2 do
--         pset(stars[i - 1], stars[i], 6)
--     end
--     for i = 2, #clouds, 2 do
--         local x, y = clouds[i - 1], clouds[i]
--         circfill(x, y, 16, 13)
--         circfill(x - 1, y + 1, 16, 1)
--     end
-- end