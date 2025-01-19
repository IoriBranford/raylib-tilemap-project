return function(obj, map)
    local sprite = obj:new_sprite(map)
    while true do
        coroutine.yield()
        if IsKeyDown(KEY_LEFT) then
            sprite.tilenamedifnew = "tile_walk2"
        elseif IsKeyDown(KEY_RIGHT) then
            sprite.tilenamedifnew = "tile_walk0"
        elseif IsKeyReleased(KEY_LEFT) then
            sprite.tilenamedifnew = "tile_stand2"
        elseif IsKeyReleased(KEY_RIGHT) then
            sprite.tilenamedifnew = "tile_stand0"
        end
    end
end