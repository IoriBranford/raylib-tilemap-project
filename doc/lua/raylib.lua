---@meta
--- Some functions from raylib
---@module 'raylib'

--- 
function ShowCursor() end

--- 
function HideCursor() end

--- 
function IsCursorHidden() end

--- 
function EnableCursor() end

--- 
function DisableCursor() end

--- 
function IsCursorOnScreen() end

--- Set target FPS (maximum)
---@param fps integer The new target FPS
function SetTargetFPS(fps) end

--- Get time in seconds for last frame drawn (delta time)
---@return number frameTime 
function GetFrameTime() end

--- Get elapsed time in seconds since InitWindow()
---@return number time 
function GetTime() end

--- Get current FPS
---@return integer fps 
function GetFPS() end

--- Set the seed for the random number generator
---@param seed integer The new random seed
function SetRandomSeed(seed) end

--- Get a random integer in range, both ends inclusive
---@param min integer Minimum
---@return integer max Maximum
---@return integer n The random number
function GetRandomValue(min) end

--- Load random values sequence, no values repeated
---@param n integer Number of random values to generate
---@param min integer Minimum value to generate
---@param max integer Maximum value to generate
---@return table sequence Array of random values
function GetRandomSequence(n, min, max) end

--- Take a screenshot
---@param file string Image file path
function TakeScreenshot(file) end

--- Open URL with default system browser (if available)
---@param url string The URL to open
function OpenURL(url) end

--- Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
---@param level integer The log level
---@param message string The message to log
function TraceLog(level, message) end

--- Set the current threshold (minimum) log level
---@param level integer A valid TraceLogLevel
function SetTraceLogLevel(level) end

--- Get a color by hue/saturation/value
---@param hue number hue from 0-360 degrees
---@param saturation number saturation from 0-1
---@param value number value from 0-1
---@return integer color color as integer 0xRRGGBBAA
function ColorFromHSV(hue, saturation, value) end

--- Get RGBA values from color integer
---@param color integer Color integer in the form 0xRRGGBBAA
---@return integer red Red value [0..255]
---@return integer green Green value [0..255]
---@return integer blue Blue value [0..255]
---@return integer alpha Alpha value [0..255]
function ColorToRGBA(color) end

--- Combine RGBA values into color integer
---@param red integer Red value [0..255]
---@param green integer Green value [0..255]
---@param blue integer Blue value [0..255]
---@param alpha integer Alpha value [0..255]
---@return integer color Color integer in the form 0xRRGGBBAA
function RGBAToColor(red, green, blue, alpha) end

