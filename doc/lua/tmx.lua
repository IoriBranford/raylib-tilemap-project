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
---@param a1 string 
---@return tmx_map newtmx_map 
function LoadMap(a1) end

--- 
---@param key string 
function tmx_map:get_property(key) end

--- 
---@param a1 integer 
---@return tmx_object r1 
function tmx_map:find_object_by_id(a1) end

--- 
---@param a1 integer 
---@return tmx_layer r1 
function tmx_map:find_layer_by_id(a1) end

--- 
---@param a1 string 
---@return tmx_layer r1 
function tmx_map:find_layer_by_name(a1) end

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
function tmx_layer:get_property(key) end

--- 
---@param map tmx_map 
---@param baseZ number 
---@param deltaZ number 
---@return table sprites 
function tmx_layer:new_sprites(map, baseZ, deltaZ) end

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
function tmx_object:get_property(key) end

