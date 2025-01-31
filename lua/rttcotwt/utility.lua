--utility

function nop() end

function xor(a, b)
    return a and not b or b and not a
end

function scopy(a)
    if a then
        local c = {}
        for i = 1, #a do
            c[i] = a[i]
        end
        return c
    end
end

function swappop(a, i)
    local e = a[i]
    a[i] = a[#a]
    a[#a] = nil
    return e
end

function cleanup(a, cond)
    for i = #a, 1, -1 do
        local o = a[i]
        if cond(o) then
            swappop(a, i)
        end
    end
end

function dir_input_x()
    return GetActionPosition("movex")
end

function dir_input_y()
    return GetActionPosition("movey")
end

function dir_input()
    return dir_input_x(),
        dir_input_y()
end

function aabbs(x, y, w, h, a, b, m, n)
    return x + w > a and x < a + m
        and y + h > b and y < b + n
end

function unitv(a, b, x, y)
    local dx, dy = x - a, y - b
    local dsq = dx * dx + dy * dy
    local dist = sqrt(dsq)
    return dx / dist, dy / dist
end