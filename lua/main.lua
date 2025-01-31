return function()
    local map = LoadMap("resources/desert.tmx")
    local sound = LoadSound("resources/keypress.ogg")
    local sprites = map:new_sprites(-100)
    local t = 0
    local obj = map:find_object_by_id(16)
    repeat until GetKeyPressed() == 0
    while true do
        coroutine.yield()
        local key = GetKeyPressed()
        while key ~= 0 do
            if key == KEY_F2 then
                ResetLuaEngine("main", 0)
                return
            end
            sound:Play()
            RunNewTask("confettiobject", 1, obj, map)
            key = GetKeyPressed();
        end
    end
end