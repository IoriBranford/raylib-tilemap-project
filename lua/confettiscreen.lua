return function()
    local map = LoadMap("resources/desert.tmx")
    local t = 0
    local obj = map:find_object_by_id(16)
    local FRAMES_PER_CONFETTI = 2
    while true do
        if t == 0 then
            task.run("confettiobject", 1, obj, map)
        end
        t = t + 1
        if t >= FRAMES_PER_CONFETTI then
            t = 0
        end
        coroutine.yield()
    end
end