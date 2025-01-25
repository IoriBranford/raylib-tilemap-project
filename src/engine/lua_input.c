#include <engine/lua.h>
#include <engine/input.h>

l_func_2_0(MapInputToAction, "Map an input to an action",
    input, string, "An input string", "",
    action, string, "An action name", "")

int L_MapInputsToActions(lua_State *l) {
    int n = 0;
    if (lua_istable(l, 1)) {
        lua_pushnil(l);
        while (lua_next(l, 1)) {
            if (lua_isstring(l, -2) && lua_isstring(l, -1)) {
                MapInputToAction(lua_tostring(l, -2), lua_tostring(l, -1));
                ++n;
            }
            lua_pop(l, 1);
        }
    }
    lua_pushinteger(l, n);
    return 1;
}
reg_func(MapInputsToActions)

doc_func(MapInputsToActions, "Map inputs to actions", 1,
    doc_var(mapping, table, "input strings as keys, action strings as values", ""),
    doc_var(numMapped, integer, "number of successful mappings", ""))

l_func_1_1(IsActionPressed, string, boolean)
l_func_1_1(IsActionDown, string, boolean)
l_func_1_1(IsActionReleased, string, boolean)
l_func_1_1(GetActionPosition, string, number)

/*
l_func_1_1(IsActionPressed, "Check if action started being pressed this frame",
                            action, string, "The action", "",
                            pressed, boolean, "If the action was just pressed")
l_func_1_1(IsActionDown,    "Check if the action is being pressed down",
                            action, string, "The action", "",
                            down, boolean, "If the action is down")
l_func_1_1(IsActionReleased, "Check if action stopped being pressed this frame",
                                action, string, "The action", "",
                                released, boolean, "If the action was just released")
l_func_1_1(GetActionPosition, "Get the position of the action",
                                action, string, "The action", "",
                                position, number, "The position")
*/

l_global_funcs_luaopen(input, 
    reg_MapInputToAction,
    reg_MapInputsToActions,
    reg_IsActionPressed,
    reg_IsActionDown,
    reg_IsActionReleased,
    reg_GetActionPosition
)