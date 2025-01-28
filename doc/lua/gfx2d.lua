---@meta
--- Graphics 2d
---@module 'gfx2d'

--- 2d graphic object
---@class Sprite
---@field x number read/write - x position
---@field y number read/write - y position
---@field z number read/write - z position
---@field width number read/write - rectangle width
---@field height number read/write - rectangle height
---@field rotationDeg number read/write - rotation in degrees
---@field originX number read-write - x position of the pivot point on rectangle
---@field originY number read-write - y position of the pivot point on rectangle
---@field color integer read/write - color in the form 0xRRGGBBAA
---@field animSpeedMS number read/write - number of milliseconds to animate sprite per-frame
---@field animTimer number read-only - number of milliseconds in the current animation state
---@field nearcamera boolean read-only - is close enough to the center of the camera
---@field tileflipx number write-only - -1 to flip, +1 to unflip
---@field tileflipy number write-only - -1 to flip, +1 to unflip
---@field tilenamed string write only - set to the name of a tile stringid defined in tileset properties
---@field tilenamedifnew string write only - as tilenamed, but preserve current animation state if already this tile
local Sprite = {}

