-- pico8

sqrt = math.sqrt
abs = math.abs
min, max = math.min, math.max
flr, ceil = math.floor, math.ceil

local MAP = LoadMap("resources/rttcotwt/rttcotwt.tmx") ---@type tmx_map
local MAPLAYER = MAP:find_layer_by_name("map") ---@type tmx_layer
local DATA = {}
for i = 0, 63 do
    DATA[i] = 0
end
local MAPZ = 0
local SPRZ = 1

function mid(...)
    local t = {...}
    table.sort(t)
    return t[ceil(#t/2)]
end

function add(t, v, i)
    return i and table.insert(t, i, v) or table.insert(t, v)
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

function cartdata(...) end --print("cartdata NYI") end
function dget(i) return DATA[i] end
function dset(i, v) DATA[i] = v end
function pal(...) end --print("pal NYI") end
function palt(...) end --print("palt NYI") end
function pset(...) end --print("pset NYI") end
function mget(x, y) return MAP:get_layer_gid(MAPLAYER, x, y) - 1 end
function mset(x, y, t) MAP:set_layer_gid(MAPLAYER, x, y, t+1) end
function fget(t, f)
    if type(t) == "number" then t = MAP:get_tile(t+1) end
    local flags = t and t:get_property("flags")
    if type(flags) ~= "number" then flags = 0 end
    if f then
        return bit.band(flags, bit.lshift(1, f)) ~= 0
    end
    return flags
end
local MUS = nil
function music(mus)
    if MUS then
        MUS:Stop()
    end
    if mus ~= -1 then
        mus:Play()
        MUS = mus
    else
        MUS = nil
    end
end
function sfx(snd)
    snd:Play()
end
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
    w, h = (w or 1)*8, (h or 1)*8
    if fx then w = -w end
    if fy then h = -h end
    local s = t:new_sprite(x, y, w, h)
    s.z = SPRZ
    s:settileSourceSize(w, h)
    return s
end
function sspr(...) end --print("sspr NYI") end
function fillp(...) end --print("fillp NYI") end
function rectfill(...) end --print("rectfill NYI") end
function circfill(...) end --print("circfill NYI") end
function circ(...) end --print("circ NYI") end
function newmap(sx, sy, dx, dy, sw, sh, layer)
    local s = MAPLAYER:new_tilelayer_sprite(MAP, sx, sy, sw, sh, dx, dy)
    s.z = MAPZ
    return s
end
function oval(...) end --print("oval NYI") end
function cls(...) end --print("cls NYI") end
function camera(...) end --print("camera NYI") end
function poke(...) end --print("poke NYI") end
function reload(...) end --print("reload NYI") end
function txt(...) end
function newtxt(t, x, y, c)
    local s = sprite.text(t, x, y, 128, 128, c)
    s.z = SPRZ
    return s
end
function sprtxt(s, t)
    s.text = t
end

function pico8_loop()
    _update60()
    _draw()
    if MUS then
        MUS:Update()
    end
end