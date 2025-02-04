-- pico8

sqrt = math.sqrt
abs = math.abs
min, max = math.min, math.max
flr, ceil = math.floor, math.ceil

local MAP = LoadMap("resources/rttcotwt.tmx") ---@type tmx_map
local MAPLAYER = MAP:find_layer_by_name("map") ---@type tmx_layer
local DATA = {}
for i = 0, 63 do
    DATA[i] = 0
end

function mid(a, b, c)
    local mx = max(a, b, c)
    local mn = min(a, b, c)
    if a ~= mx and a ~= mn then
        return a
    end
    if b ~= mx and b ~= mn then
        return b
    end
    return c
end

function add(t, v, i)
    return table.insert(t, i, v)
end

function rnd(i)
    return math.random()*(i or 1)
end

function all(t)
    local i = 0
    return function()
        i = i + 1
        return t[i]
    end
end

function cartdata(...) print("cartdata NYI") end
function dget(i) return DATA[i] end
function dset(i, v) DATA[i] = v end
function pal(...) print("pal NYI") end
function palt(...) print("palt NYI") end
function pset(...) print("pset NYI") end
function mget(x, y) return MAP:get_layer_gid(MAPLAYER, x, y) - 1 end
function mset(x, y, t) MAP:set_layer_gid(MAPLAYER, x, y, t+1) end
function fget(t, f)
    if type(t) == "number" then t = MAP:get_tile(t+1) end
    local flags = tile and tile:get_property("flags")
    if type(flags) ~= "number" then flags = 0 end
    if f then
        return bit.band(flags, bit.lshift(1, f)) ~= 0
    end
    return flags
end
function music(...) print("music NYI") end
function sfx(...) print("sfx NYI") end
function sprpos(s, x, y)
    if x then s.x = x end
    if y then s.y = y end
end
function sprflip(s, fx, fy)
    if fx ~= nil then s.tileflipx = fx and -1 or 1 end
    if fy ~= nil then s.tileflipy = fy and -1 or 1 end
end
function sprtile(s, t)
    local w, h = s.width, s.height
    if type(t) == "number" then t = MAP:get_tile(t+1) end
    s.tile = t
    s:settileSourceSize(w, h)
end
function newspr(t, x, y, w, h, fx, fy)
    if type(t) == "number" then t = MAP:get_tile(t+1) end
    if not t then return end
    w, h = w*8, h*8
    if fx then w = -w end
    if fy then h = -h end
    local s = t:new_sprite(x, y, w, h)
    s:settileSourceSize(w, h)
    return s
end
function sspr(...) print("sspr NYI") end
function fillp(...) print("fillp NYI") end
function rectfill(...) print("rectfill NYI") end
function circfill(...) print("circfill NYI") end
function circ(...) print("circ NYI") end
function newmap(sx, sy, dx, dy, sw, sh, layer)
    return MAPLAYER:new_tilelayer_sprite(MAP, sx, sy, sw, sh, dx, dy)
end
function oval(...) print("oval NYI") end
function cls(...) print("cls NYI") end
function camera(...) print("camera NYI") end
function poke(...) print("poke NYI") end
function reload(...) print("reload NYI") end