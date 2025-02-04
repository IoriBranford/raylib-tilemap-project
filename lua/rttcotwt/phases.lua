--game phases

function draw_credits()
    draw_objs()
end

function update_credits()
    update_objs()
    if IsActionPressed("jump") then
        ResetLuaEngine("rttcotwt", 0)
    end
end

function start_credits()
    cam:setposition(0, 0)
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
            ResetLuaEngine("rttcotwt", 0)
        end
    elseif obj_dead(enemy) then
        start_credits()
    end
end

function draw_game()
    draw_objs()
    draw_clock()
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
        update_lifebar(ninstartlife)
    end
end

function draw_title()
    draw_objs()
    txt("best", 80, 123, 7)
    draw_clock()
end

function start_title()
    reload(0x2000, 0x2000, 0x1000)
    pal()
    poke(0X5F5C, 0)
    clear_game_objs()
    clock_loadbest()
    cam:setposition(0, 0)
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
    add_lifebar()
    update_lifebar(ninstartlife)
    _update60 = update_title
    _draw = draw_title
end