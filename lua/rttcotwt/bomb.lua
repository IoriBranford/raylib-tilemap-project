--bombs
local splitbombwholegrav = -1 / 16
local splitbombhalfgrav = 1 / 16
local fwallgrav = -1 / 32
local flamegrav = -1 / 32
local fbombexpldist = 16
local godbombspeed = 3
local splitbombmaxvely = 1.5
local fusecolors = { 8, 14, 7 }

function draw_bomb(o)
    local secs = ceil((o.fuse or -1) / 60)
    local clr = fusecolors[secs]
    if clr then
        print(secs, o.x + 2, o.y - 8, clr)
    end
    draw_obj_spr(o)
    if clr then
        pset(o.x + 2 + rnd(4),
            o.y - 1 + rnd(4),
            clr)
    end
end

function update_expl(o)
    o.x = o.x + (o.vx or 0)
    o.y = o.y + (o.vy or 0)
    update_obj_ani(o)
    if obj_ani_ending(o) then
        kill_obj(o)
    end
end

function add_puff(o)
    add_obj_spr(o)
    o.update = update_expl
    return o
end

function add_normal_expl(cx, cy)
    add_puff {
        x = cx - 8, y = cy - 8,
        ani = sprs.expl.tl,
    }
    add_puff {
        x = cx, y = cy - 8,
        ani = sprs.expl.tr,
    }
    add_puff {
        x = cx - 8, y = cy,
        ani = sprs.expl.bl,
    }
    add_puff {
        x = cx, y = cy,
        ani = sprs.expl.br,
    }
    add(expls, add_obj_spr {
        x = cx - 4, y = cy - 4,
        ani = sprs.expl.ctr,
        update = update_expl
    })
end

function add_flame_puffs(cx, cy)
    add_puff {
        x = cx - 8, y = cy - 8,
        ani = sprs.flameexpl.left,
    }
    add_puff {
        x = cx, y = cy - 8,
        ani = sprs.flameexpl.right,
    }
end

function add_flame_expl(cx, cy)
    add_flame_puffs(cx, cy)
    add(expls, add_obj_spr {
        x = cx - 4, y = cy - 4,
        ani = sprs.flamepuff,
        update = update_expl
    })
end

function bomb_explode(o)
    o.addexpl(obj_spr_center(o))
    kill_obj(o)
end

function update_bomb_normal(o)
    o.y = o.y + o.vy
    update_obj_ani(o)
    obj_fall_out_y(o)
end

function update_bomb_split_whole(o)
    local bombs, ay = enbombs, splitbombwholegrav
    if o.target == enemy then
        bombs, ay = ninbombs, -ay
    end
    local vy = o.vy
    vy = ay < 0
        and max(0, vy + ay)
        or min(0, vy + ay)
    if vy == 0 then
        add(bombs, add_bomb({
            x = o.x,
            y = o.y,
            vx = -.25,
            vy = -.25
        }, "splithalf"))
        add(bombs, add_bomb({
            x = o.x,
            y = o.y,
            vx = .25,
            vy = -.25
        }, "splithalf"))
        add_puff {
            x = o.x, y = o.y,
            vy = -.5,
            ani = sprs.splitpuff
        }
        kill_obj(o)
    end
    o.vy = vy
    o.x, o.y = o.x + o.vx, o.y + vy
    update_obj_ani(o)
    obj_fall_out_y(o)
end

function update_bomb_split_half(o)
    local vx, vy = o.vx, o.vy
    -- if vx<0 then
    --  vx=min(0,vx+.0625)
    -- elseif vx>0 then
    --  vx=max(0,vx-.0625)
    -- end
    local ay = o.target == enemy
        and -splitbombhalfgrav
        or splitbombhalfgrav
    vy = min(vy + ay, splitbombmaxvely)
    o.vx, o.vy = vx, vy
    o.x, o.y = o.x + vx, o.y + vy
    update_obj_ani(o)
    obj_fall_out_y(o)
end

function update_fwall_bomb(o)
    local bombs, ay = enbombs, fwallgrav
    if o.target == enemy then
        bombs, ay = ninbombs, -ay
    end
    local vy = o.vy
    vy = ay < 0
        and max(.25, vy + ay)
        or min(-.25, vy + ay)
    o.dist = (o.dist or 0) + abs(vy)
    if o.dist >= 32 then
        for vx = -2, 2 do
            add(bombs, add_bomb({
                target = o.target,
                x = o.x,
                y = o.y,
                vx = vx,
                vy = o.target == enemy
                    and -1.5 or 1.5,
                ax = vx * -.0625
            }, "flame"))
        end
        add_puff {
            x = o.x, y = o.y,
            vy = -.5,
            ani = sprs.flamepuff
        }
        kill_obj(o)
    end
    o.vy = vy
    o.x, o.y = o.x + o.vx, o.y + vy
    update_obj_ani(o)
    obj_fall_out_y(o)
end

function update_fwall_flame(o)
    local vx, vy, ax = o.vx, o.vy, o.ax
    if vx < 0 then
        vx = min(0, vx + ax)
    elseif vx > 0 then
        vx = max(0, vx + ax)
    end
    local ay = o.target == enemy
        and -flamegrav
        or flamegrav
    if ay < 0 then
        vy = max(vy + ay, 1)
    else
        vy = min(vy + ay, -1)
    end
    o.dist = (o.dist or 0) + abs(vy)
    o.vx, o.vy = vx, vy
    o.x, o.y = o.x + vx, o.y + vy
    update_obj_ani(o)
    if o.dist >= 80 then
        add_flame_puffs(obj_spr_center(o))
        kill_obj(o)
    end
end

function update_fbomb_expls(o)
    if o.age % 6 == 0 then
        local dist = (o.expldist or 0) + 4
        o.expldist = dist
        local cx, cy = obj_spr_center(o)
        for dy = -1, 1, 2 do
            for dx = -1, 1, 2 do
                add(expls, add_normal_expl(
                    cx + dx * dist, cy + dy * dist
                ))
            end
        end
    end
    if o.age >= 30 then
        kill_obj(o)
    end
end

function update_fbomb_preexpl(o)
    update_obj_ani(o)
    local target = o.target
    local cx, cy = obj_spr_center(o)
    local tx, ty = obj_spr_center(target)
    local vx, vy = unitv(cx, cy, tx, ty)
    o.vx, o.vy = vx * .5, vy * .5
    o.x, o.y = o.x + o.vx, o.y + o.vy
    local t = (o.t or 30) - 1
    o.t = t
    if t <= 0 then
        bomb_explode(o)
        add_obj({
            x = o.x,
            y = o.y,
            w = o.w,
            h = o.h,
            update = update_fbomb_expls
        })
    end
end

function update_fbomb_fall(o)
    update_obj_ani(o)
    if o.x < 8 then
        o.vx = abs(o.vx)
    elseif o.x > 112 then
        o.vx = -abs(o.vx)
    end
    o.x, o.y = o.x + o.vx, o.y + o.vy
    local tx, ty = o.target.x, o.target.y
    if not o.target.dying
        and abs(tx - o.x) < fbombexpldist
        and abs(ty - o.y) < fbombexpldist then
        o.vx, o.vy = 0, 0
        o.update = update_fbomb_preexpl
    end
end

function update_godbomb_fly(o)
    o.x, o.y = o.x + o.vx, o.y + o.vy
    update_obj_ani(o)
    obj_fall_out_y(o)
end

function update_godbomb_prefly(o)
    o.y = o.y + o.vy
    o.dist = (o.dist or 0) + abs(o.vy)
    if o.dist >= 16 then
        local vx, vy = 0, -1
        if not o.target.hidden then
            local cx, cy = obj_spr_center(o)
            local tx = o.target.x + (o.target.w << 2)
            local ty = o.target.y
            vx, vy = unitv(cx, cy, tx, ty)
        end
        o.vx, o.vy = vx * godbombspeed, vy * godbombspeed
        o.update = update_godbomb_fly
        sfx(snds.godbomb)
    end
    update_obj_ani(o)
end

function update_bomb_fuse(o)
    o.fuse = o.fuse - 1
    if o.fuse <= 0 then
        bomb_explode(o)
    end
    update_obj_ani(o)
end

function start_bomb_fuse(o)
    o.fuse = abs(o.fuse)
    o.updateonthrow = o.updateonthrow or o.update
    o.update = update_bomb_fuse
end

function start_bomb_thrown(o)
    o.update = o.updateonthrow
    o.updateonthrow = nil
    o.fuse = -1
    o.target = enemy
    o.flpy = true
    o.dist = nil
end

bombtmpls = {
    normal = {
        fuse = 180,
        vx = 0,
        vy = 1.5,
        ani = sprs.bomb.normal,
        update = update_bomb_normal,
    },
    split = {
        fuse = 180,
        vx = 0,
        vy = 2,
        ani = sprs.bomb.split,
        update = update_bomb_split_whole,
    },
    splithalf = {
        fuse = 180,
        ani = sprs.bomb.split,
        update = update_bomb_split_half,
    },
    fwall = {
        fuse = 180,
        vx = 0,
        vy = 1.5,
        ani = sprs.bomb.fwall,
        update = update_fwall_bomb,
    },
    flame = {
        h = 2,
        fuse = 0,
        cantcatch = true,
        ani = sprs.flame,
        addexpl = add_flame_expl,
        update = update_fwall_flame,
    },
    fbomb = {
        fuse = 180,
        vx = 1.5,
        vy = 1.5,
        ani = sprs.fbomb,
        update = update_fbomb_fall,
        updateonthrow = update_fbomb_fall,
    },
    godbomb = {
        fuse = 180,
        vy = .5,
        ani = sprs.godbomb,
        update = update_godbomb_prefly,
        updateonthrow = update_godbomb_prefly,
    }
}

function add_bomb(o, tmpl)
    if type(tmpl) == "string" then
        tmpl = bombtmpls[tmpl]
    end
    tmpl = type(tmpl) == "table" and tmpl
        or bombtmpls.normal
    for k, v in pairs(tmpl) do
        o[k] = v
    end
    add_obj_spr(o)
    o.draw = draw_bomb
    o.fuse = -o.fuse
    o.addexpl = o.addexpl
        or add_normal_expl
    return o
end

function obj_explode_bombs(o, bombs)
    local heldbomb = o.bomb
    for bomb in all(bombs) do
        if bomb ~= o
            and bomb ~= heldbomb
            and aabbs(o.x, o.y,
                o.w << 3, o.h << 3,
                bomb.x + (bomb.w << 1),
                bomb.y + (bomb.w << 1),
                bomb.w << 2, bomb.h << 2)
        then
            bomb_explode(bomb)
        end
    end
end

function obj_hit_any_expl(o)
    for expl in all(expls) do
        if aabbs(o.x, o.y,
                o.w << 3, o.h << 3,
                expl.x, expl.y,
                expl.w << 3, expl.h << 3)
        then
            return expl
        end
    end
end