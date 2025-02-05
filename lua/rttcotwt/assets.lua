
-- asset handling
function apply_spr_base(spr, base)
    local typ = type(spr)
    if typ == "number" then
        return spr + base
    end

    if typ == "table" then
        local i = spr.i
        if i then
            spr.i = i + base
        end

        for i = 1, #spr do
            spr[i] = apply_spr_base(spr[i], base)
        end
    end
    return spr
end

function apply_sprs_bases(sprs)
    for name, spr in pairs(sprs) do
        local base = type(spr) == "table"
            and spr._base
        if base then
            for name, subspr in pairs(spr) do
                spr[name] = apply_spr_base(subspr, base)
            end
        end
    end
end

-- game assets
snds = {
    gamemus = LoadMusicStream("resources/rttcotwt/music0.ogg"),
    titlemus = LoadMusicStream("resources/rttcotwt/music9.ogg"),
    deadmus = LoadMusicStream("resources/rttcotwt/music15.ogg"),
    endmus = LoadMusicStream("resources/rttcotwt/music16.ogg"),
    finalmus = LoadMusicStream("resources/rttcotwt/music22.ogg"),

    step = LoadSound("resources/rttcotwt/sound32.wav"),
    jump = LoadSound("resources/rttcotwt/sound33.wav"),
    nindie = LoadSound("resources/rttcotwt/sound34.wav"),
    expl = LoadSound("resources/rttcotwt/sound35.wav"),
    expl2 = LoadSound("resources/rttcotwt/sound36.wav"),
    catch = LoadSound("resources/rttcotwt/sound38.wav"),
    engetup = LoadSound("resources/rttcotwt/sound39.wav"),
    throw = LoadSound("resources/rttcotwt/sound40.wav"),
    split = LoadSound("resources/rttcotwt/sound41.wav"),
    bdrop = LoadSound("resources/rttcotwt/sound42.wav"),
    fwall = LoadSound("resources/rttcotwt/sound43.wav"),
    change = LoadSound("resources/rttcotwt/sound47.wav"),
    godbomb = LoadSound("resources/rttcotwt/sound48.wav")
}

local pals = {
    burn1 = { 4, 9, 10, 4, 9, 10, 4, 9, 10, 4, 9, 10, 4, 9, 10 },
    burn2 = { 9, 10, 4, 9, 10, 4, 9, 10, 4, 9, 10, 4, 9, 10, 4 },
    burn3 = { 10, 4, 9, 10, 4, 9, 10, 4, 9, 10, 4, 9, 10, 4, 9 },
}

sprs = {
    heart = 64,
    expl = {
        _base = 67,
        tl = { t = 6, 0, 1, 2, 3 },
        tr = { t = 6, flpx = true, 0, 1, 2, 3 },
        bl = { t = 6, flpy = true, 0, 1, 2, 3 },
        br = { t = 6, flpx = true, flpy = true, 0, 1, 2, 3 },
        ctr = { t = 6, { i = 4, sfx = snds.expl }, 5, 4, 5 }
    },
    bomb = {
        _base = 16,
        normal = {
            0,
            { i = 0, pal = { [5] = 8, [1] = 2 } },
            t = 6
        },
        split = {
            0,
            { i = 0, pal = { [5] = 11, [1] = 3 } },
            t = 6
        },
        fwall = {
            0,
            { i = 0, pal = { [5] = 9, [1] = 4 } },
            t = 6
        }
    },
    puff = {
        t = 3,
        28,
        29,
        30,
        31
    },
    splitpuff = {
        t = 3,
        pal = { [6] = 3 },
        { i = 28, sfx = snds.split, },
        29,
        30,
        31
    },
    fbomb = {
        t = 6,
        34,
        { i = 35, pal = { [5] = 10, [1] = 9 } }
    },
    flame = {
        t = 3,
        36,
        37,
        38,
        39
    },
    flameexpl = {
        _base = 80,
        right = { 0, 1, 2, 3, 4, t = 3 },
        left = { 0, 1, 2, 3, 4, t = 3, flpx = true },
    },
    flamepuff = {
        t = 3,
        pal = { [6] = 9, [5] = 8 },
        { i = 28, sfx = snds.fwall },
        29,
        30,
        31
    },
    godbomb = {
        t = 1,
        { i = 0, palt = 0xfcff, pal = { [6] = 7, [7] = 12 } },
        { i = 0, palt = 0xfdfb, pal = { [6] = 7, [13] = 12 } },
        { i = 0, palt = 0xbdff, pal = { [6] = 7, [1] = 12 } },
        { i = 0, palt = 0xddff, pal = { [6] = 7, [2] = 12 } },
        { i = 0, palt = 0xf9ff, pal = { [6] = 7, [5] = 12 } },
    },
    enemyskull = {
        _base = 88,
        run = { t = 6, 0, 4 },
        warpout = {
            t = 6,
            { i = 0, fillp = "▒" },
            { i = 4, fillp = "▒" },
            { i = 0, fillp = "░" },
            { i = 4, fillp = "░" },
        },
        warpin = {
            t = 6,
            { i = 0, fillp = "░" },
            { i = 4, fillp = "░" },
            { i = 0, fillp = "▒" },
            { i = 4, fillp = "▒" },
        },
        throw = { i = 2, t = 30, sfx = snds.bdrop },
        jump = 2,
        knocked = {
            t = 3,
            { i = 4, pal = pals.burn1 },
            { i = 4, pal = pals.burn2 },
            { i = 4, pal = pals.burn3 },
        },
        getup = { i = 4, t = 60, sfx = snds.change },
    },
    ninja = {
        _base = 128,
        idle = { 0, 1, t = 15 },
        prejump = 2,
        jump = {
            loop = 6,
            { i = 3, t = 9, sfx = snds.jump },
            { i = 20, t = 3 },
            { i = 21, t = 3 },
            { i = 20, t = 3, flpx = true, flpy = true },
            { i = 21, t = 3, flpx = true, flpy = true },
            { i = 39, t = 3 },
            { i = 40, t = 3 }
        },
        blownup = {
            t = 3,
            loop = 3,
            { i = 4, t = 6,        pal = pals.burn2, sfx = snds.nindie },
            { i = 5, t = 6,        pal = pals.burn3 },
            { i = 35, pal = pals.burn1 },
            { i = 36, pal = pals.burn2 },
            { i = 35, pal = pals.burn3 },
            { i = 36, pal = pals.burn1 },
            { i = 35, pal = pals.burn2 },
            { i = 36, pal = pals.burn3 },
        },
        -- die={4,5,6,t=12},
        -- swim={7,8,9,8,t=6},
        run = {
            16,
            { i = 17, sfx = snds.step },
            18,
            { i = 17, sfx = snds.step },
            t = 6
        },
        -- roll={20,21,
        --  {i=20,flpx=true,flpy=true},
        --  {i=21,flpx=true,flpy=true},
        --  t=6
        -- },
        -- crawl={22,23,t=12},
        duck = 23,
        -- froze=24,
        hang = 33,
        climb = {
            32,
            { i = 33, sfx = snds.step },
            { i = 32, flpx = true },
            { i = 33, flpx = true, sfx = snds.step },
            t = 6
        },
        wall = 34,
        fall = { 35, 36, t = 3 },
        fire = { 37, 38, 37, t = 6 },
        zip = { 39, 40, t = 3 },
        -- swing={48,49,t=6},
        -- attack={t=6,
        --  {i=50,palt=0b1100100001100000,pal={[5]=13}},
        --  {i=50,palt=0b1000110001100000,pal={[1]=13}},
        --  {i=50,palt=0b1000110001000000,pal={[1]=13}},
        --  {i=50,palt=0b1000110000100000,pal={[1]=13}},
        --  {i=50,palt=0b1000010001100000,pal={[1]=13}},
        -- },
        -- poss={51,52,53,t=6},
    },
    enemy = {
        _base = 192,
        idle = { 0, 2, t = 10 },
        run = { 4, 6, 8, 10, t = 6 },
        jump = 12,
        drop = 14,
        prethrow = 34,
        throw = { i = 32, t = 30, sfx = snds.bdrop },
        knocked = {
            t = 3,
            { i = 40, pal = pals.burn1 },
            { i = 40, pal = pals.burn2 },
            { i = 40, pal = pals.burn3 },
        },
        getup = { i = 46, t = 30, sfx = snds.engetup },
    },
    ladder = 189,
    plane = {
        _base = 1,
        fwd = 0,
        down = 2,
        up = 4
    },
    gameover = 7
}
apply_sprs_bases(sprs)