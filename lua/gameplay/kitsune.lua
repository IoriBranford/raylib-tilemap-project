return function(obj, map)
    MapInputsToActions({
        ["KAXIS_-LEFT+RIGHT"] = "movex",
        ["KAXIS_-A+D"] = "movex",
        ["P0_BAXIS_-LEFT_FACE_LEFT+LEFT_FACE_RIGHT"] = "movex",
        P0_AXIS_LEFT_X = "movex",
        KEY_LEFT = "movex-",
        KEY_RIGHT = "movex+",
        KEY_A = "movex-",
        KEY_D = "movex+",
    })
    local sprite = obj:new_sprite(map)
    local tilename = "tile_stand0"
    sprite.tilenamedifnew = tilename
    while true do
        coroutine.yield()
        local movex = GetActionPosition("movex")
        if movex < 0 then
            tilename = "tile_walk2"
        elseif movex > 0 then
            tilename = "tile_walk0"
        elseif tilename == "tile_walk0" then
            tilename = "tile_stand0"
        elseif tilename == "tile_walk2" then
            tilename = "tile_stand2"
        end
        sprite.tilenamedifnew = tilename
    end
end