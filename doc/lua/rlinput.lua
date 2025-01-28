---@meta
--- Input functions and constants from Raylib
---@module 'rlinput'

--- Get key pressed (keycode), call it multiple times for keys queued
---@return integer key The next KeyboardKey in the queue, or 0 when the queue is empty
function GetKeyPressed() end

--- Get char pressed (unicode), call it multiple times for chars queued
---@return integer chara The next Unicode character in the queue, or 0 when the queue is empty
function GetCharPressed() end

--- Set a custom key to exit program (default is ESC)
---@param key integer A valid KeyboardKey
function SetExitKey(key) end

--- Set gamepad vibration for both motors (duration in seconds)
---@param gamepad integer Index of the gamepad
---@param leftMotor number Left motor vibration strength [0-1]
---@param rightMotor number Right motor vibration strength [0-1]
---@param duration number How long to vibrate in seconds
function SetGamepadVibration(gamepad, leftMotor, rightMotor, duration) end

--- Did mouse button go from up to down this frame
---@param button integer A MouseButton
---@return boolean pressed Mouse button was pressed
function IsMouseButtonPressed(button) end

--- Is mouse button currently down this frame
---@param button integer A MouseButton
---@return boolean down Mouse button is down
function IsMouseButtonDown(button) end

--- Did mouse button go from down to up this frame
---@param button integer A MouseButton
---@return boolean released Mouse button was released
function IsMouseButtonReleased(button) end

--- Is mouse button currently up this frame
---@param button integer A MouseButton
---@return boolean up Mouse button is up
function IsMouseButtonUp(button) end

--- Get mouse position X
---@return integer x X position
function GetMouseX() end

--- Get mouse position Y
---@return integer y Y position
function GetMouseY() end

--- Get mouse position XY
---@return number pos.x Mouse position
---@return number pos.y Mouse position
function GetMousePosition() end

--- Get mouse delta between frames
---@return number delta.x Mouse delta
---@return number delta.y Mouse delta
function GetMouseDelta() end

--- Set mouse position
---@param x integer X position
---@param y integer Y position
function SetMousePosition(x, y) end

--- Set mouse offset
---@param x integer X offset
---@param y integer Y offset
function SetMouseOffset(x, y) end

--- Set mouse scale
---@param x integer X scale
---@param y integer Y scale
function SetMouseScale(x, y) end

--- Get mouse wheel movement for X or Y, whichever is larger
---@return number movement The wheel movement
function GetMouseWheelMove() end

--- Get mouse wheel movement for both X and Y
---@return number movement.x The wheel movement
---@return number movement.y The wheel movement
function GetMouseWheelMoveV() end

--- Set mouse cursor
---@param cursor integer A valid MouseCursor
function SetMouseCursor(cursor) end

