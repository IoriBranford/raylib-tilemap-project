---@meta
--- raylib audio
---@module 'rlaudio'

--- raylib Sound
---@class Sound
local Sound = {}

--- 
---@param a1 string 
---@return Sound newSound 
function LoadSound(a1) end

--- 
function Sound:Play() end

--- 
function Sound:Stop() end

--- 
function Sound:Pause() end

--- 
function Sound:Resume() end

--- raylib Music
---@class Music
local Music = {}

--- 
---@param a1 string 
---@return Music newMusic 
function LoadMusicStream(a1) end

--- 
function Music:Play() end

--- 
function Music:Stop() end

--- 
function Music:Update() end

--- 
function Music:Pause() end

--- 
function Music:Resume() end

