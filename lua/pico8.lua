-- pico8

sqrt = math.sqrt
abs = math.abs
min, max = math.min, math.max
flr, ceil = math.floor, math.ceil

MAP = nil ---@type tmx_map
MAPL = nil ---@type tmx_layer

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
function dget(...) print("dget NYI") end
function dset(...) print("dset NYI") end
function pal(...) print("pal NYI") end
function palt(...) print("palt NYI") end
function pset(...) print("pset NYI") end
function mget(...) print("mget NYI") end
function mset(...) print("mset NYI") end
function fget(...) print("fget NYI") end
function music(...) print("music NYI") end
function sfx(...) print("sfx NYI") end
function spr(...) print("spr NYI") end
function sspr(...) print("sspr NYI") end
function fillp(...) print("fillp NYI") end
function rectfill(...) print("rectfill NYI") end
function circfill(...) print("circfill NYI") end
function circ(...) print("circ NYI") end
function map(...) print("map NYI") end
function oval(...) print("oval NYI") end
function cls(...) print("cls NYI") end
function camera(...) print("camera NYI") end
function poke(...) print("poke NYI") end
function reload(...) print("reload NYI") end