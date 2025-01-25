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

doc_func(MapInputsToActions, "Map inputs to actions", 1,
    doc_var(mapping, table, "input strings as keys, action strings as values", ""),
    doc_var(numMapped, integer, "number of successful mappings", ""))


l_global_funcs_luaopen(input, 
    l_func_reg(MapInputToAction),
    l_func_reg(MapInputsToActions),
    l_func_reg(IsActionPressed),
    l_func_reg(IsActionDown),
    l_func_reg(IsActionReleased),
    l_func_reg(GetActionPosition)
)