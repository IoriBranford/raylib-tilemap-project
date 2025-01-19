return function()
    local map = LoadMap("resources/tenkou.tmx")
    local startObjects = map:find_layer_by_name("startObjects").objects
    local sprites = {}
    local z = #startObjects
    for _, obj in ipairs(startObjects) do
        local sprite = obj:new_sprite(map)
        sprite.z = z
        z = z - 1
        sprites[#sprites+1] = sprite
    end
    while true do
        coroutine.yield()
    end
end