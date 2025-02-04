-- object
local objs = {}

function draw_obj_text(o)
    pal()
    fillp(o.fillp or "█")
    local text = o.text
    local typ = type(text)
    if typ == "table" then
        local y = o.y
        local lineh = o.lineh or 8
        for i = 1, #text do
            print(text[i], o.x, y, o.clr)
            y = y + 8
        end
    elseif typ == "string" then
        print(text, o.x, o.y, o.clr)
    end
end

function draw_obj_circ(o)
    local circ = o.fill and circfill
        or circ
    circ(o.x, o.y, o.rad, o.clr)
end

-- function draw_obj_sspr(o)
--     local sx, sy = o.sx, o.sy
--     local sw, sh = o.sw, o.sh
--     local i = o.spri
--     if i and not (sx and sy) then
--         sx = bit.lshift(bit.band(i,  0xF), 3)
--         sy = bit.rshift(bit.band(i, ~0xF), 1)
--     end
--     sw = sw or bit.lshift((o.w or 1), 3)
--     sh = sh or bit.lshift((o.h or 1), 3)
--     pal(o.pal)
--     palt(o.palt or 0x8000)
--     fillp((o.fillp or "█"))--|0b.01)
--     sspr(sx or 0, sy or 0,
--         sw, sh,
--         o.x, o.y,
--         o.dw or sw, o.dh or sh,
--         xor(o.flpx, o.frmflpx),
--         xor(o.flpy, o.frmflpy))
-- end

function draw_obj_spr(o)
    -- if o.dw or o.dh then
    --     draw_obj_sspr(o)
    --     return
    -- end
    pal(o.pal)
    palt(o.palt or 0x8000)
    fillp((o.fillp or "█"))--|0b.01)
    sprpos(o.spr, o.x, o.y)
    sprflip(o.spr,
        xor(o.flpx, o.frmflpx),
        xor(o.flpy, o.frmflpy))
end

function draw_obj_map(o)
    pal(o.pal)
    palt(o.palt or 0x8000)
    fillp((o.fillp or "█"))--|0b.01)
    sprpos(o.spr, o.x, o.y)
end

function add_obj(o)
    add(objs, o)
    o.age = 0
    o.x = o.x or 0
    o.y = o.y or 0
    o.update = o.update or nop
    o.draw = o.draw or nop
end

function add_obj_circ(o)
    add_obj(o)
    o.rad = o.rad or 1
    o.clr = o.clr or 1
    o.draw = draw_obj_circ
end

function add_obj_text(o)
    add_obj(o)
    o.clr = o.clr or 7
    o.lineh = o.lineh or 8
    o.draw = draw_obj_text
end

function set_obj_frm(o, fi)
    fi = fi or 1
    local ani = o.ani
    local spri, ft,
    flpx, flpy,
    palt, pal,
    fillp, snd
    local typ = type(ani)
    if typ == "number" then
        spri = ani
    elseif typ == "table" then
        local f = ani[fi]
        typ = type(f)
        if typ == "table" then
            spri = f.i
            ft = f.t
            flpx = xor(f.flpx, ani.flpx)
            flpy = xor(f.flpy, ani.flpy)
            palt = f.palt
            pal = f.pal
            fillp = f.fillp
            snd = f.sfx
        else
            spri = typ == "number" and f
            flpx = ani.flpx
            flpy = ani.flpy
        end
        spri = spri or ani.i
        ft = ft or ani.t
        palt = palt or ani.palt
        pal = pal or ani.pal
        fillp = fillp or ani.fillp
        snd = snd or ani.sfx
    end
    if snd then
        sfx(snd)
    end
    sprtile(o.spr, spri or 1)
    o.fi = fi
    o.ft = ft or 1
    o.frmflpx = flpx
    o.frmflpy = flpy
    o.palt = palt
    o.pal = pal
    o.fillp = fillp
end

function start_obj_ani(o, ani, fi)
    o.ani = ani
    set_obj_frm(o, fi)
end

function update_obj_ani(o, ani)
    if ani and ani ~= o.ani then
        start_obj_ani(o, ani)
        return
    end
    ani = o.ani
    local typ = type(ani)
    local n = typ == "table" and #ani or 1
    local ft = o.ft - 1
    if ft == 0 then
        local fi = o.fi
        if fi >= n then
            fi = typ == "table" and ani.loop or 1
        else
            fi = fi + 1
        end
        set_obj_frm(o, fi)
    else
        o.ft = ft
    end
end

function add_obj_spr(o)
    add_obj(o)
    o.w = o.w or 1
    o.h = o.h or 1
    if (o.draw or nop) == nop then
        o.draw = draw_obj_spr
    end
    if o.ani then
        start_obj_ani(o, o.ani, o.fi)
    end
    o.spri = o.spri or 1
    o.spr = newspr(o.spri, o.x, o.y, o.w, o.h,
        xor(o.flpx, o.frmflpx),
        xor(o.flpy, o.frmflpy))
    return o
end

function obj_spr_center(o)
    return o.x + (bit.lshift(o.w, 2)),
        o.y + (bit.lshift(o.h, 2))
end

function obj_frm_ending(o)
    return (o.ft or 1) <= 1
end

function obj_ani_ending(o)
    local ani = o.ani
    local n = type(ani) == "table" and #ani or 1
    return n <= (o.fi or 1) and obj_frm_ending(o)
end

function add_obj_map(o)
    add_obj(o)
    o.draw = draw_obj_map
    o.celx = o.celx or 0
    o.cely = o.cely or 0
    o.celw = o.celw or 1
    o.celh = o.celh or 1
    o.spr = newmap(o.celx, o.cely, o.x, o.y, o.celw, o.celh, o.layer)
end

function obj_dead(o)
    return o.age < 0
end

function kill_obj(o)
    o.age = -0x8000
end

function update_objs()
    for i = 1, #objs do
        local o = objs[i]
        o.age = o.age + 1
        o:update()
    end
end

function draw_objs()
    for i = 1, #objs do
        local o = objs[i]
        o:draw()
    end
end

function cleanup_dead_objs()
    cleanup(objs, obj_dead)
end

function clear_objs()
    for i = #objs, 1, -1 do
        objs[i] = nil
    end
end