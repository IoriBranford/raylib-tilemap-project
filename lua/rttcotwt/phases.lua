--game phases

local stars = {}
for y = 16, 80, 32 do
    for x = 16, 80, 32 do
        add(stars, x + rnd(32))
        add(stars, y + rnd(32))
    end
end
local clouds = {}
for y = 120, 128, 8 do
    for x = 0, 112, 16 do
        add(clouds, x + rnd(16))
        add(clouds, y + rnd(16))
    end
end

function draw_sky()
    pal()
    fillp("░")
    rectfill(0, 104, 128, 108, 1)
    fillp("▒")
    rectfill(0, 108, 128, 128, 1)
    fillp()
    circfill(96, 24, 4, 6)
    for i = 2, #stars, 2 do
        pset(stars[i - 1], stars[i], 6)
    end
    for i = 2, #clouds, 2 do
        local x, y = clouds[i - 1], clouds[i]
        circfill(x, y, 16, 13)
        circfill(x - 1, y + 1, 16, 1)
    end
end

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

function draw_credits()
    cls()
    draw_sky()
    draw_objs()
end

function update_credits()
    update_objs()
    if IsActionPressed("jump") then
        start_title()
    end
end

function start_credits()
    camera()
    clear_game_objs()
    add_obj_text {
        x = 16, y = 128,
        update = function(o)
            local vy = IsActionDown("movey")
                and -1 or -.125
            o.y = max(8, o.y + vy)
        end,
        text = [[
   A toy box jam 2023 GAME

   CONCEPT
   DESIGN
   PROGRAM

    iori branford

   GRAPHICS
   SOUNDS

    tom hall
    lafolie
    toby hefflin

   MUSIC

    gruber
   ]]
    }
    add_obj_text {
        text = "🅾️close",
        x = 96, y = 120
    }
    music(snds.endmus)
    _update60 = update_credits
    _draw = draw_credits
end

function update_game()
    if not clockpaused
        and clock < clocklimit then
        clock = clock + 1
    end
    update_objs()
    cleanup_dead_objs()
    cleanup(enbombs, obj_dead)
    cleanup(ninbombs, obj_dead)
    cleanup(expls, obj_dead)

    if obj_dead(ninja) then
        if IsActionPressed("jump") or IsActionPressed("throw") then
            start_title()
        end
    elseif obj_dead(enemy) then
        start_credits()
    end
end

function draw_game()
    cls()
    draw_sky()
    camera(cam.x, cam.y)
    draw_objs()
    camera()
    draw_life(ninja.life)
    draw_clock()
    if obj_dead(ninja) then
        spr(sprs.gameover,
            64 - 16, 64 - 8,
            4, 2)
    end
    if hazeptn and hazeclr then
        fillp(hazeptn)
        rectfill(0, 0, 128, 128, hazeclr)
    end
end

function start_game()
    local lvl = nil
    cam.x = 0
    cam.y = worldbtm - 128
    if lvl then
        cam.y = cam.y - 128 * lvl
    end
    clear_game_objs()
    add_rooms()
    enemy = add_enemy(lvl)
    ninja = add_ninja()
    add_plane()
    poke(0X5F5C, 255)
    music(snds.gamemus)
    _update60 = update_game
    _draw = draw_game
end

function update_title()
    if IsActionPressed("jump") then
        start_game()
    elseif IsActionPressed("throw") then
        start_credits()
    elseif IsActionPressed("movex") then
        if GetActionPosition("movex") < 0 then
            ninstartlife = max(1, ninstartlife - 1)
        else
            ninstartlife = min(ninmaxstartlife,
                ninstartlife + 1)
        end
    end
end

function draw_title()
    cls()
    draw_sky()
    draw_objs()
    draw_life(ninstartlife)
    print("best", 80, 123, 7)
    draw_clock()
end

function start_title()
    reload(0x2000, 0x2000, 0x1000)
    pal()
    poke(0X5F5C, 0)
    clear_game_objs()
    clock_loadbest()
    camera()
    add_obj_text {
        x = 8, y = 48,
        text = [[
   rise to the commander
     of the wolf triad

   "⬅️"/"➡️" set starting life 1-9
   🅾️ start game
   ❎ view credits
   ]]
    }
    music(snds.titlemus)
    _update60 = update_title
    _draw = draw_title
end