--enemy
local enemyrunspd = 2
local enemyhopvely = -4
local enemyhopgrav = 1 / 4
local enemyhurtvely = -2
local enemyhurttime = 60
local enemyjumpvely = -4
local enemygrav = 1 / 8

function enemy_hit_objs(o)
    obj_explode_bombs(o, ninbombs)
    if obj_hit_any_expl(o) then
        start_enemy_hurt(o)
        return true
    end
end

function update_enemy_shot(o)
    if enemy_hit_objs(o) then
        return
    end
    if obj_ani_ending(o) then
        start_enemy_move(o)
        return
    end
    update_obj_ani(o, o.sprset.throw)
end

function start_enemy_shot(o)
    o.vx = 0
    o.vy = 0
    o.readytofire = nil
    o.update = update_enemy_shot
    update_obj_ani(o, o.sprset.throw)
    local b = add_bomb({
        target = ninja,
        x = o.x + (o.w*2),
        y = o.y + (o.h*2)
    }, o.bombtmpl)
    if o.flpx and b.vx then
        b.vx = -b.vx
    end
    add(enbombs, b)
end

function set_enemy_level(o, l)
    o.level = l
    local lvl = enemylevels[l]
    if lvl then
        for k, v in pairs(lvl) do
            o[k] = v
        end
        o.ladderdrops = scopy(o.ladderdrops)
    end
end

function update_enemy_jump(o)
    local ladders = o.ladderdrops
    if ladders then
        local ly = o.laddery or o.y
        for i, lx in ipairs(ladders) do
            if lx then
                local c, r = room_cell(lx, ly)
                local spri = mget(c, r)
                if fget(spri, breakflag)
                    or not fget(spri, solidflag) then
                    mset(c, r, sprs.ladder)
                else
                    ladders[i] = false
                end
            end
        end
        o.laddery = ly + 8
    end
    o.y = o.y + o.vy
    update_obj_ani(o, o.sprset.jump)
    if o.y <= o.floory then
        o.y = o.floory
        o.laddery = nil
        set_enemy_level(o, o.level + 1)
        start_enemy_move(o)
    end
end

function start_enemy_jump(o)
    o.vy = enemyjumpvely
    o.floory = o.y - 128
    o.update = update_enemy_jump
    clock_pause(nil)
end

function update_enemy_warpin(o)
    update_obj_ani(o, o.sprset.warpin)
    if obj_ani_ending(o) then
        start_enemy_shot(o)
    end
end

function update_enemy_hiding(o)
    o.hidetime = o.hidetime + 1
    if o.hidetime > 120 then
        o.x = 8 + rnd(96)
        o.flpx = ninja.x < o.x
        o.spr.alpha = 255
        o.hidetime = nil
        o.update = update_enemy_warpin
    end
end

function update_enemy_warpout(o)
    update_obj_ani(o, o.sprset.warpout)
    if obj_ani_ending(o) then
        o.spr.alpha = 0
        o.hidetime = 0
        o.update = update_enemy_hiding
    end
end

function update_enemy_getup(o)
    update_obj_ani(o, o.sprset.getup)
    if obj_ani_ending(o) then
        start_enemy_jump(o)
    end
end

function update_enemy_dying(o)
    update_obj_ani(o)
    local i = (o.dyingtime or 0) + 1
    o.dyingtime = i
    if i <= 300 then
        if i > 240 then
            o.fillp = "░"
        elseif i > 180 then
            o.fillp = "▒"
        end
        if i % 6 == 0 then
            add_normal_expl(o.x + rnd(16), o.y + rnd(16))
        end
        if i == 300 then
            o.spr.alpha = 0
            hazeptn = "░"
            hazeclr = 0
        end
    elseif i == 330 then
        hazeptn = "▒"
    elseif i == 360 then
        hazeptn = "█"
    elseif i == 480 then
        kill_obj(o)
    end
end

function enemy_change(o)
    add_obj_spr({
        x = o.x,
        y = o.y,
        vy = -.5,
        w = o.w,
        h = o.h,
        flpx = o.flpx,
        ani = o.ani,
        update = update_obj_disintegrate
    })
    o.sprset = sprs.enemyskull
end

function update_enemy_hurt(o)
    update_obj_ani(o, o.sprset.knocked)
    o.vy = o.vy + enemygrav
    o.y = o.y + o.vy
    if o.y >= o.floory then
        o.y = o.floory
        local time = o.time or 0
        time = time + 1
        if time > enemyhurttime then
            o.time = nil
            if o.level < #enemylevels then
                if o.level + 1 == #enemylevels then
                    enemy_change(o)
                end
                o.update = update_enemy_getup
                local mus = enemylevels[o.level + 1].music
                if mus then
                    music(mus)
                end
            else
                clock_savebest()
                o.update = update_enemy_dying
            end
        else
            o.time = time
        end
    end
end

function enemy_say_taunt(o)
    local taunt = o.taunt
    if taunt then
        o.taunt = nil
        add_obj_text {
            text = taunt,
            x = 0, y = 16,
            clr = 0xFF8080FF,
            update = function(o)
                o.x = camobj.x
                o.y = camobj.y + 24
                if o.age >= 180 then
                    kill_obj(o)
                end
            end
        }
    end
end

function start_enemy_hurt(o)
    o.vx = 0
    o.vy = enemyhurtvely
    o.update = update_enemy_hurt
    ninja.invul = 180
    if o.level >= #enemylevels
        or enemylevels[o.level + 1].music then
        music(-1)
    end
    sfx(snds.expl2)
    clock_pause(true)
end

function enemy_move_x(o)
    local x = o.x + o.vx
    if x >= 104 then
        o.x = 104
        o.vx = -o.vx
        o.readytofire = true
    elseif x < 8 then
        o.x = 8
        o.vx = -o.vx
        o.readytofire = true
    else
        o.x = x
    end
    o.flpx = o.vx < 0
end

function enemy_hop_y(o)
    local vy = o.vy + enemyhopgrav
    local y = o.y + vy
    if y >= o.floory then
        y = o.floory
        vy = enemyhopvely
    end
    o.y, o.vy = y, vy
end

function enemy_try_fire(o)
    if ninja.y < o.y + 128
        and o.readytofire
        and o.y == o.floory then
        local firedistx = o.firedistx or 2
        local dx = ninja.x + (ninja.w*4)
            - (o.x + (o.w*4))
        if abs(dx) < firedistx then
            start_enemy_shot(o)
            return true
        end
    end
end

function update_enemy_hop(o)
    if enemy_hit_objs(o) then
        return
    end
    if ninja.y < o.floory + 128 then
        enemy_say_taunt(o)
    end
    if enemy_try_fire(o) then
        return
    end
    enemy_move_x(o)
    enemy_hop_y(o)
    update_obj_ani(o,
        o.vy < 0 and o.sprset.jump
        or o.sprset.drop)
end

function update_enemy_run(o)
    if enemy_hit_objs(o) then
        return
    end
    if ninja.y < o.y + 128 then
        enemy_say_taunt(o)
    end
    if enemy_try_fire(o) then
        return
    end
    enemy_move_x(o)
    update_obj_ani(o, o.sprset.run)
end

function start_enemy_move(o)
    o.vx = o.flpx and -enemyrunspd
        or enemyrunspd
    o.vy = 0
    o.readytofire = nil
    o.update = o.movefunc or update_enemy_run
end

enemylevels = {
    [1] = {
        bombtmpl = bombtmpls.normal,
        ladderdrops = { 32, 88 },
        movefunc = update_enemy_run,
        taunt = "          here, catch!          "
    },
    [2] = {
        bombtmpl = bombtmpls.split,
        ladderdrops = { 24 },
        firedistx = 4,
        movefunc = update_enemy_run,
        taunt = "        double your pain!       "
    },
    [3] = {
        bombtmpl = bombtmpls.fwall,
        ladderdrops = { 104 },
        firedistx = 8,
        movefunc = update_enemy_run,
        taunt = "          you're toast!         "
    },
    [4] = {
        bombtmpl = bombtmpls.fbomb,
        firedistx = 128,
        ladderdrops = { 16 },
        movefunc = update_enemy_hop,
        taunt = "       x marks your grave!      "
    },
    [5] = {
        music = snds.finalmus,
        bombtmpl = bombtmpls.godbomb,
        movefunc = update_enemy_warpout,
        firedistx = 32,
    }
}

function add_enemy(lvl)
    lvl = lvl or 1
    local o = add_obj_spr {
        x = 56, y = mapbtm - 128 * (1 + lvl),
        vx = 0, vy = 0,
        w = 2, h = 2,
        sprset = sprs.enemy
    }
    o.floory = o.y
    set_enemy_level(o, lvl)
    start_enemy_move(o)
    return o
end