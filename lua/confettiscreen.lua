return function()
    local map = LoadMap("resources/desert.tmx")
    local t = 0
    local obj = map:find_object_by_id(16)
    repeat until GetKeyPressed() == 0
    while true do
        coroutine.yield()
        while GetKeyPressed() ~= 0 do
            task.run("confettiobject", 1, obj, map)
        end
    end
end