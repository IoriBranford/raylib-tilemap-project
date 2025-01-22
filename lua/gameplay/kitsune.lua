return function(obj, map)
    MapInputsToActions({
        KEY_LEFT = "movex-",
        KEY_RIGHT = "movex+",
    })
    local sprite = obj:new_sprite(map)
    local tilename = "tile_stand0"
    sprite.tilenamedifnew = tilename
    while true do
        coroutine.yield()
        local goingLeft, goingRight = IsActionDown("movex-"), IsActionDown("movex+")
        if goingLeft and not goingRight then
            tilename = "tile_walk2"
            sprite.tilenamedifnew = tilename
        elseif not goingLeft and goingRight then
            tilename = "tile_walk0"
            sprite.tilenamedifnew = tilename
        elseif tilename == "tile_walk0" then
            tilename = "tile_stand0"
            sprite.tilenamedifnew = tilename
        elseif tilename == "tile_walk2" then
            tilename = "tile_stand2"
            sprite.tilenamedifnew = tilename
        end
    end
end