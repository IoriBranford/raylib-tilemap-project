---@meta
--- 
---@module 'tmx'

--- 
---@class tmx_map
---@field width integer width in tiles
---@field height integer height in tiles
---@field tile_width integer width of a tilelayer cell
---@field tile_height integer height of a tilelayer cell
---@field properties table properties as key/value table
local tmx_map = {}

--- 
---@param path string 
---@return tmx_map newtmx_map 
function LoadMap(path) end

--- 
---@param key string 
---@return any value
function tmx_map:get_property(key) end

--- 
---@param id integer 
---@return tmx_object object 
function tmx_map:find_object_by_id(id) end

--- 
---@param id integer 
---@return tmx_layer layer 
function tmx_map:find_layer_by_id(id) end

--- 
---@param name string 
---@return tmx_layer layer 
function tmx_map:find_layer_by_name(name) end

--- 
---@param gid integer 
---@return tmx_tile tile
function tmx_map:get_tile(gid) end

--- 
---@param layer tmx_layer
---@param x number
---@param y number
---@return integer gid
function tmx_map:get_layer_gid(layer, x, y) end
--- 
---@param layer tmx_layer
---@param x number
---@param y number
---@param gid integer
function tmx_map:set_layer_gid(layer, x, y, gid) end

--- 
---@param layer tmx_layer
---@param x number
---@param y number
---@return tmx_tile tile
---@return boolean flipx
---@return boolean flipy
function tmx_map:get_layer_tile(layer, x, y) end
--- 
---@param layer tmx_layer
---@param x number
---@param y number
---@param tile tmx_tile
---@param flipx boolean
---@param flipy boolean
function tmx_map:set_layer_tile(layer, x, y, tile, flipx, flipy) end

--- 
---@param baseZ number 
---@return table sprites 
function tmx_map:new_sprites(baseZ) end

--- 
---@class tmx_layer
---@field id integer unique layer id
---@field class_type string user-defined type or class name
---@field type integer L_LAYER, L_OBJGR, L_GROUP, or L_IMAGE
---@field properties table properties as key/value table
local tmx_layer = {}

--- 
---@param key string 
---@return any value
function tmx_layer:get_property(key) end

--- 
---@param map tmx_map 
---@param baseZ number 
---@param deltaZ number 
---@return table sprites 
function tmx_layer:new_sprites(map, baseZ, deltaZ) end

--- 
---@param map tmx_map 
---@param sourceX number? 
---@param sourceY number? 
---@param sourceWidth number? 
---@param sourceHeight number? 
---@param destX number? 
---@param destY number? 
---@param destWidth number? 
---@param destHeight number? 
---@return table sprites 
function tmx_layer:new_tilelayer_sprite(map, sourceX, sourceY, sourceWidth, sourceHeight, destX, destY, destWidth, destHeight) end

--- 
---@class tmx_object
---@field id integer unique object id
---@field type string user-defined type or class
---@field x number x
---@field y number y
---@field width number width
---@field height number height
---@field properties table properties
local tmx_object = {}

--- 
---@param key string 
---@return any value
function tmx_object:get_property(key) end

--- 
---@class tmx_tile
---@field id integer tile id within its tileset
---@field type string user-defined type or class
---@field width number width
---@field height number height
---@field properties table properties
---@field collision tmx_object[]
local tmx_tile = {}

--- 
---@param key string 
---@return any value
function tmx_tile:get_property(key) end

--- 
---@param x number
---@param y number
---@param w number
---@param h number
---@param rotationDeg number?
---@param color integer? 0xRRGGBBAA - default white (0xFFFFFFFF)
---@return Sprite sprite
function tmx_tile:new_sprite(x, y, w, h, rotationDeg, color) end