--ninja

ninstartlife = 5
ninmaxstartlife = 9
local ninrunaccel = .25
local nintoprunspd = 1.5
local nintopfallspd = 4
local ningrav = 1 / 8
local ninclimbaccel = .5
local nintopclimbspd = 1.5
local ninjumpvely = -2
local ninjumpinvely = -3
local ninblownoutvely = -3
local ninthrowbombvely = -4
local nininvul = 180

function update_nin_invul(o)
    if o.invul then
        o.invul = o.invul - 1
        if o.invul <= 0 then
            o.invul = nil
        end
    end
end

function nin_update_held_bomb(o)
    local b = o.bomb
    if b then
        if obj_dead(b) then
            o.bomb = nil
        else
            b.x, b.y = o.x, o.y - 4
        end
    end
end

function cam_on_nin(o)
    local vy = mid(-camtopspd, o.y - 96 - cam.y, camtopspd)
    cam.y = min(cam.y + vy, worldbtm - 128)
end

function update_nin_death(o)
    update_obj_ani(o, sprs.ninja.blownup)
    o.vy = o.vy + ningrav
    o.y = o.y + o.vy
    if o.y > cam.y + 128 then
        if o.life > 0 then
            o.dying = nil
            o.y = cam.y + 128
            start_nin_jumpin(o)
        else
            sfx(-1)
            music(snds.deadmus)
            kill_obj(o)
            clock_pause(true)
            add_game_over()
        end
    end
end

function nin_start_dying(o)
    o.life = o.life - 1
    update_lifebar(life)
    if o.life <= 0 then
        music(-1)
    end
    o.vx = 0
    o.vy = ninblownoutvely
    o.dying = true
    o.update = update_nin_death
    if o.bomb then
        bomb_explode(o.bomb)
        o.bomb = nil
    end
end

function nin_hit_objs(o)
    if not o.invul then
        obj_explode_bombs(o, enbombs)
        if obj_hit_any_expl(o) then
            nin_start_dying(o)
        end
    end
end

function nin_coll_vy(x, y, w, h, vy)
    local bnd, edge, cmp

    if vy < 0 then
        bnd = -10000
        edge = y
        cmp = max
    elseif vy > 0 then
        bnd = mapbtm
        edge = y + h
        cmp = min
    else
        return 0
    end

    for x = x, x + w - 1, w - 1 do
        local cbnd = cell_bound(x, edge, 1, vy)
        if cbnd then
            bnd = cbnd
            break
        end
    end
    return cmp(0, bnd - edge)
end

function nin_coll_vx(x, y, w, h, vx)
    local bnd, edge, cmp

    if vx < 0 then
        bnd = 0
        edge = x
        cmp = max
    elseif vx > 0 then
        bnd = 128
        edge = x + w
        cmp = min
    else
        return 0
    end

    -- check only his top corner against block
    -- so he can mantle onto block's top corner
    -- for y=y,y+h-1,h-1 do
    local cbnd = cell_bound(edge, y, 0, vx)
    if cbnd then
        bnd = cbnd
        -- break
    end
    -- end
    return cmp(0, bnd - edge)
end

function nin_move_x(o)
    local inx = dir_input_x()
    local vx, vy = o.vx, o.vy
    if inx == 0 then
        if vx < 0 then
            vx = min(vx + ninrunaccel, 0)
        elseif vx > 0 then
            vx = max(0, vx - ninrunaccel)
        end
    else
        vx = mid(-nintoprunspd, vx + inx * ninrunaccel, nintoprunspd)
    end
    vx = vx + nin_coll_vx(o.x + vx, o.y, bit.lshift(o.w, 3), bit.lshift(o.h, 3), vx)
    o.vx = vx
    o.x = o.x + vx
end

function nin_climb_y(o)
    local iny = dir_input_y()
    local vy = o.vy
    if iny == 0 then
        if vy < 0 then
            vy = min(vy + ninclimbaccel, 0)
        elseif vy > 0 then
            vy = max(0, vy - ninclimbaccel)
        end
    else
        vy = mid(-nintopclimbspd, vy + iny * ninclimbaccel, nintopclimbspd)
    end
    local collvy = nin_coll_vy(o.x, o.y + vy, bit.lshift(o.w, 3), bit.lshift(o.h, 3), vy)
    vy = vy + collvy
    o.vy = vy
    o.y = o.y + vy
    return collvy
end

function nin_drop_y(o)
    local vx, vy = o.vx, o.vy
    vy = min(vy + ningrav, nintopfallspd)
    vy = vy + nin_coll_vy(o.x, o.y + vy, bit.lshift(o.w, 3), bit.lshift(o.h, 3), vy)
    o.vy = vy
    o.y = o.y + vy
end

function update_nin_flpx(o, dirx)
    if dirx ~= 0 then
        o.flpx = dirx < 0
    end
end

function update_nin_air_ani(o)
    update_nin_flpx(o, dir_input_x())
    update_obj_ani(o, sprs.ninja.jump)
end

function update_nin_ground_ani(o)
    local inx = dir_input_x()
    update_nin_flpx(o, inx)
    local ani
    if inx ~= 0 then
        ani = sprs.ninja.run
    else
        ani = sprs.ninja.idle
    end
    update_obj_ani(o, ani)
end

function nin_try_jump(o, holdok)
    if holdok and IsActionDown("jump") or IsActionPressed("jump") then
        o.vy = ninjumpvely
        o.update = update_nin_air
        return true
    end
end

function nin_catch_allowed(o)
    return not o.bomb and not o.dying
        and not o.climbing
end

function nin_catch_box(o)
    local w, h = bit.lshift(o.w, 3), bit.lshift(o.h, 2)
    return o.x, o.y - h, w, h
end

function nin_find_catch_bomb(o)
    local x, y, w, h = nin_catch_box(o)
    for i = 1, #enbombs do
        local b = enbombs[i]
        if not b.cantcatch
            and aabbs(x, y, w, h,
                b.x, b.y,
                bit.lshift(b.w, 3), bit.lshift(b.h, 3))
        then
            return b, i
        end
    end
end

function nin_find_coming_bomb(o)
    local bomb, dst = nil, 0x7fff
    local x, y, w, h = nin_catch_box(o)
    local warnh = 96
    y, h = y - warnh, h + warnh
    local heldbomb = o.bomb
    for b in all(enbombs) do
        if b ~= heldbomb
            and not b.cantcatch
            and aabbs(x, y, w, h,
                b.x, b.y,
                bit.lshift(b.w, 3), bit.lshift(b.h, 3))
        then
            local d = y + warnh - b.y - (bit.lshift(b.h, 3))
            if d < dst then
                bomb, dst = b, d
            end
        end
    end
    return bomb, dst
end

function nin_try_catch_bomb(o)
    if not (IsActionPressed("movey") and GetActionPosition("movey") < 0)
    and not IsActionPressed("throw") then
        return
    end
    local bomb = o.bomb
    if bomb then
        o.bomb = nil
        add(ninbombs, bomb)
        start_bomb_thrown(bomb)
        bomb.vy = ninthrowbombvely
        sfx(snds.throw)
    else
        local bi
        bomb, bi = nin_find_catch_bomb(o)
        if bomb then
            bomb.vx = 0
            bomb.vy = 0
            o.bomb = bomb
            swappop(enbombs, bi)
            start_bomb_fuse(bomb)
            sfx(snds.catch)
            return bomb
        end
    end
end

function update_nin_climb_ani(o)
    local iny = dir_input_y()
    local ani
    if iny ~= 0 then
        ani = sprs.ninja.climb
    else
        ani = sprs.ninja.hang
    end
    update_obj_ani(o, ani)
end

function update_nin_climb(o)
    o.climbing = true
    nin_hit_objs(o)
    if o.dying then
        o.climbing = nil
        return
    end
    update_nin_invul(o)
    if nin_try_jump(o) then
        o.vx = nintoprunspd * dir_input_x()
        o.climbing = nil
    else
        local collvy = nin_climb_y(o)
        if collvy < 0 then
            o.update = update_nin_ground
            o.climbing = nil
        elseif not obj_ladder(o) then
            o.update = update_nin_air
            o.climbing = nil
        end
    end
    update_nin_climb_ani(o)
    cam_on_nin(o)
end

function nin_try_climb(o)
    local iny = dir_input_y()
    local climbldr = iny ~= 0
        and not o.bomb
        and obj_ladder(o)
    if climbldr then
        o.jumpagain = nil
        o.x = climbldr
        o.vx = 0
        o.vy = min(0, o.vy)
        o.update = update_nin_climb
        return true
    end
end

function update_nin_air(o)
    nin_try_catch_bomb(o)
    nin_hit_objs(o)
    if o.dying then
        return
    end
    update_nin_invul(o)
    nin_drop_y(o)
    nin_move_x(o)
    o.jumpagain = o.jumpagain or IsActionPressed("jump")
    if nin_try_climb(o) then
    elseif obj_ground(o) then
        if o.jumpagain and nin_try_jump(o, true) then
        else
            o.update = update_nin_ground
        end
        o.jumpagain = nil
    end
    nin_update_held_bomb(o)
    update_nin_air_ani(o)
    cam_on_nin(o)
end

function update_nin_ground(o)
    nin_try_catch_bomb(o)
    nin_hit_objs(o)
    if o.dying then
        return
    end
    update_nin_invul(o)
    nin_move_x(o)
    if nin_try_climb(o) then
    elseif nin_try_jump(o) then
    else
        local grnd = obj_ground(o)
        if grnd then
            o.vy = grnd - o.y - (bit.lshift(o.h, 3))
            o.y = o.y + o.vy
        else
            o.update = update_nin_air
        end
    end
    nin_update_held_bomb(o)
    update_nin_ground_ani(o)
    cam_on_nin(o)
end

function update_nin_jumpin(o)
    local vy = o.vy
    vy = min(vy + ningrav, nintopfallspd)
    o.vy = vy
    o.y = o.y + vy
    update_nin_air_ani(o)
    if o.vy > 0 then
        clock_pause(nil)
        o.update = update_nin_air
        return
    end
end

function start_nin_jumpin(o)
    o.vx = 0
    o.vy = ninjumpinvely
    o.invul = nininvul
    o.update = update_nin_jumpin
end

function update_plane_flyin(o)
    o.vx = o.vx + o.ax
    o.vy = o.vy + o.ay
    o.x = o.x + o.vx
    o.y = o.y + o.vy
    if o.nin then
        o.nin.x = o.x + 4
        o.nin.y = o.y - 4
        -- cam_on_nin(o.nin)
    end
    if o.vy >= 0 then
        o.ax = abs(o.ax)
        if o.nin then
            start_nin_jumpin(o.nin)
            o.nin = nil
        end
    end
    if o.x > 128 then
        kill_obj(o)
    end
    update_obj_ani(o,
        o.vy < -1 and sprs.plane.up
        or o.vy > 1 and sprs.plane.down
        or sprs.plane.fwd)
end

function add_plane()
    return add_obj_spr {
        ani = sprs.plane.up,
        x = -16, y = cam.y + 88,
        w = 2, h = 2,
        vx = 2.5, vy = -2,
        ax = -1 / 32, ay = .0625,
        nin = ninja,
        update = update_plane_flyin
    }
end

function draw_ninja(o)
    if (o.invul or 0) % 4 <= 1 then
        draw_obj_spr(o)
    end
    if nin_catch_allowed(o)
        or o.climbing then
        local b, d = nin_find_coming_bomb(o)
        if b then
            d = max(0, d)
            local x, y, w, h = nin_catch_box(o)
            local clr, fp = 5, "░"
            if d < 32 then
                clr, fp = 7, "█"
            elseif d < 64 then
                clr, fp = 6, "▒"
            end
            pal()
            fillp(fp)
            oval(x - bit.lshift(d, 1), y - d, x + w + bit.lshift(d, 1), y + h + d, clr)
            if o.climbing then
                print("⬅️\n🅾️", o.x - 8, o.y, 7)
                print("➡️\n🅾️", o.x + 8, o.y, 7)
            else
                print("❎", x + 1, y, clr)
            end
            fillp()
        end
    end
end

function add_ninja()
    return add_obj_spr {
        x = -8, y = worldbtm - 8,
        ani = sprs.ninja.duck,
        life = ninstartlife,
        draw = draw_ninja
    }
end