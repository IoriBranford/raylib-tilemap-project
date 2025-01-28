---@meta
--- Functions for binding device inputs to game actions
---@module 'input'

--- Map an input to an action
---@param input string An input string
---@param action string An action name
function MapInputToAction(input, action) end

--- Map inputs to actions
---@param mapping table input strings as keys, action strings as values
---@return integer numMapped number of successful mappings
function MapInputsToActions(mapping) end

--- Did action go from up to down this frame
---@param action string Name of the action
---@return boolean pressed Action was pressed
function IsActionPressed(action) end

--- Is action currently down this frame
---@param action string Name of the action
---@return boolean down Action is down
function IsActionDown(action) end

--- Did action go from down to up this frame
---@param action string Name of the action
---@return boolean released Action was released
function IsActionReleased(action) end

--- Get action's position this frame
---@param action string Name of the action
---@return number position Position of the action - [0..1] for buttons, [-1..1] for axes
function GetActionPosition(action) end

