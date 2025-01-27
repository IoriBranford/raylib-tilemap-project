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

l_func_1_1(IsActionPressed, "Did action go from up to down this frame",
    action, string, "Name of the action", "",
    pressed, boolean, "Action was pressed")
l_func_1_1(IsActionDown, "Is action currently down this frame",
    action, string, "Name of the action", "",
    down, boolean, "Action is down")
l_func_1_1(IsActionReleased, "Did action go from down to up this frame",
    action, string, "Name of the action", "",
    released, boolean, "Action was released")
l_func_1_1(GetActionPosition, "Get action's position this frame",
    action, string, "Name of the action", "",
    position, number, "Position of the action - [0..1] for buttons, [-1..1] for axes")

int luaopen_input(lua_State *l)
{
    lua_getglobal(l, "_G");
    luaL_Reg r[] = {reg_MapInputToAction, reg_MapInputsToActions, reg_IsActionPressed, reg_IsActionDown, reg_IsActionReleased, reg_GetActionPosition, {0}};
    luaL_register(l, ((void *)0), r);
    doc_module(input, "Functions for binding device inputs to game actions",
        doc_module_constants()
        doc_module_classes()
        doc_module_funcs(
            doc_MapInputToAction, doc_MapInputsToActions, doc_IsActionPressed, doc_IsActionDown, doc_IsActionReleased, doc_GetActionPosition        
    ))
    return 0;
}