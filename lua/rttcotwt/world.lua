--game world
ninja, enemy, enbombs, ninbombs, expls = nil, nil, nil, nil, nil
hazeclr, hazeptn = nil, nil
solidflag = 0
ladderflag = 1
breakflag = 2

local rooms = {  --<y,{celx,cely}>
    [0] = { 0, 0 },
    [128] = { 0, 16 },
    [256] = { 16, 0 },
    [384] = { 16, 16 },
    [512] = { 32, 0 },
    [640] = { 32, 16 },
}
local roomsprs = {}
mapbtm = 768
worldbtm = mapbtm + 88

clocklimit = 60 * 60 * 9
clock, clockpaused = nil, nil

local save = {
    besttime = 0
}

function clear_game_objs()
    clear_objs()
    ninja = nil
    enemy = nil
    enbombs = {}
    ninbombs = {}
    expls = {}
    hazeclr = nil
    hazeptn = nil
    clock = 0
    clockpaused = true
end

function clock_pause(pause)
    clockpaused = pause
end

function clock_savebest()
    local besttime = dget(save.besttime)
    if clock < besttime then
        dset(save.besttime, clock)
    end
end

function clock_loadbest()
    clock = dget(save.besttime)
    if clock == 0 then
        clock = clocklimit
        dset(save.besttime, clocklimit)
    end
end

function room_cell(x, y)
    x, y = flr(x), flr(y)
    local room = rooms[flr(y/128)*128]
    if room then
        return
            room[1] + bit.rshift(x % 128, 3),
            room[2] + bit.rshift(y % 128, 3)
    end
end

function cell_bound(x, y, axis, dir)
    local c, r = room_cell(x, y)
    if c and fget(mget(c, r), solidflag) then
        local v = axis > 0 and y or x
        local bnd = flr(v/8)*8
        if (dir or 1) < 0 then
            bnd = bnd + 8
        end
        return bnd
    end
end

function obj_ground(o)
    local w, h = bit.lshift(o.w, 3), bit.lshift(o.h, 3)
    local x, y = o.x, o.y + h
    for x = x, x + w - 1, w - 1 do
        local bnd = cell_bound(x, y, 1, 1)
        if bnd then
            return bnd
        end
    end
end

function cell_ladder(x, y, axis)
    local c, r = room_cell(x, y)
    if c and fget(mget(c, r), ladderflag) then
        local v = axis > 0 and y or x
        return flr(v/8)*8
    end
end

function obj_ladder(o)
    local w, h = bit.lshift(o.w, 3), bit.lshift(o.h, 3)
    local x, y = o.x, o.y
    for x = x, x + w - 1, w - 1 do
        local ldr = cell_ladder(x, y, 0)
        if ldr then
            return ldr
        end
    end
end

function add_rooms()
    for y, room in pairs(rooms) do
        add(roomsprs, newmap(
            room[1], room[2],
            0, y,
            16, 16))
    end
end

function obj_fall_out_y(o)
    if o.y < 0
        and o.y + (bit.lshift(o.w, 3)) < cam.y
        or o.y > cam.y + 128 then
        kill_obj(o)
    end
end

function update_obj_disintegrate(o)
    update_obj_ani(o)
    o.x = o.x + (o.vx or 0)
    o.y = o.y + (o.vy or 0)
    if o.age > 40 then
        kill_obj(o)
    elseif o.age > 20 then
        o.fillp = "░"
    else
        o.fillp = "▒"
    end
end